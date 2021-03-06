#include "ModbusLink.h"

ModbusSlaveLink::ModbusSlaveLink(USART &uart) :com(uart)
{
	this->OnUpdateRegHoid = 0;
}
#include "Buffer.h"
bool ModbusSlaveLink::CheckFrame()
{
	int rxlen = com.RxSize();

	if (com.GetBytes(&rxFrame.data[rxFrame.Length], rxlen))
	{
		rxFrame.Length += rxlen;
	}
	//判断数据帧最小长度要求
	if (rxFrame.Length < 8)
		return false;
#ifdef  DEBUG
	Buffer(rxFrame.data, rxFrame.Length).ShowHex(true);
#endif //  DEBUG	
	if (!rxFrame.CheckFrame())
		return false;
	else
		return true;
}

bool ModbusSlaveLink::Send()
{
	if (!txFrame.isUpdated) //no new frame data, no need to send
		return false;	
	txFrame.data[0] = txFrame.Address;
	txFrame.data[1] = txFrame.Code;
	txFrame.Crc2 = Crc::CRC16RTU(txFrame.data, txFrame.frameLength - 2);
	txFrame.data[txFrame.frameLength - 2] = txFrame.Crc2 & 0xff;
	txFrame.data[txFrame.frameLength - 1] = txFrame.Crc2 >> 8;
	com.SendBytes(txFrame.data, txFrame.frameLength);
	txFrame.isUpdated = false;
	rxFrame.RemoveOneFrame();//移除处理完的接收数据帧
	txFrame.Cnt++;
	return true;
}

//处理数据帧
void ModbusSlaveLink::DealFrame()
{
	if ((this->rxFrame.Address != this->id) && (this->rxFrame.Address != 0))
		return;

	switch (this->rxFrame.Code)
	{
	case 4:
		//强置单线圈。强置一个逻辑线圈的通断状态
		//读取输入寄存器
		//处理广播地址
		if (this->rxFrame.Address == 0)
			break;		
		if (this->dealRegInputRead(this->rxFrame.regAddr, this->rxFrame.regLength) == 0)
		{
			this->txFrame.frameLength = this->rxFrame.regLength * 2 + 5;
			this->txFrame.isUpdated = true;
			this->Send();
		}
		break;
	case 3:
		//读取输入寄存器。在一个或多个输入寄存器中取得当前的二进制值
		//读取保持寄存器
		//处理广播地址
		if (this->rxFrame.Address == 0)
			break;
					
		if (this->dealRegHoildRead(this->rxFrame.regAddr, this->rxFrame.regLength) == 0)
		{
			this->txFrame.frameLength = this->rxFrame.regLength * 2 + 5;
			this->txFrame.isUpdated = true;
			this->Send();
		}
		break;
	case 6:
		//读取异常状态。取得8个内部线圈的通断状态，这8个线圈的地址由控制器决定
		debug_printf("WriteSingleRegister address %d value %d\n", this->rxFrame.regAddr, this->rxFrame.regLength);
		//预置单寄存器
		
		//this->rxFrame.regLength即为需要设置的值
		if (this->dealRegHoildWriteOne(this->rxFrame.regAddr, this->rxFrame.regLength) == 0)
		{
			//处理广播地址
			if (this->rxFrame.Address == 0)
				break;
			this->txFrame.Address = this->id;
			this->txFrame.Code = 6;
			this->txFrame.regLength = this->rxFrame.regLength;
			this->txFrame.data[2] = this->rxFrame.data[2];
			this->txFrame.data[3] = this->rxFrame.data[3];
			this->txFrame.data[4] = this->rxFrame.data[4];
			this->txFrame.data[5] = this->rxFrame.data[5];

			this->txFrame.frameLength = 8;
			this->txFrame.isUpdated = true;
			this->Send();
		}
		break;
	case 16:
		//报告从机标识。可使主机判断编址从机的类型及该从机运行指示灯的状态
		//设置多个寄存器		
		debug_printf("WriteMultipleRegisters\n");
		if (this->dealRegHoildWrite(this->rxFrame.regAddr, this->rxFrame.regLength) == 0)
		{
			//处理广播地址
			if (this->rxFrame.Address == 0)
				break;
			this->txFrame.Address = this->id;
			this->txFrame.Code = 16;
			this->txFrame.regLength = this->rxFrame.regLength;
			this->txFrame.data[2] = this->rxFrame.data[2];
			this->txFrame.data[3] = this->rxFrame.data[3];
			this->txFrame.data[4] = this->rxFrame.data[4];
			this->txFrame.data[5] = this->rxFrame.data[5];
			this->txFrame.frameLength = 8;
			this->txFrame.isUpdated = true;
			this->Send();
		}
		break;
	default:
		break;
	}
}
//设置输入寄存器
void ModbusSlaveLink::SetRegInput(int addr0, int reglen, uint16_t* reg, int reggroup)
{
	//非法寄存器组
	if (reggroup >= ModbusSlaveLink::RegInputLen)
		return;
	this->RegInputs[reggroup].Addr0 = addr0;
	this->RegInputs[reggroup].Lenth = reglen;
	this->RegInputs[reggroup].Reg = reg;
}
//设置保持寄存器
void ModbusSlaveLink::SetRegHoid(int addr0, int reglen, uint16_t* reg, int reggroup)
{
	//非法寄存器组
	if (reggroup >= ModbusSlaveLink::RegHoildingLen)
		return;
	this->RegHoildings[reggroup].Addr0 = addr0;
	this->RegHoildings[reggroup].Lenth = reglen;
	this->RegHoildings[reggroup].Reg = reg;
}
//处理读取输入寄存器 0 正确 1 非法地址 2非法长度
int ModbusSlaveLink::dealRegInputRead(uint16_t addr, uint16_t len)
{
	int ret = this->searchRegInGroup(addr,len);
	if (ret == -1)
		return 1;
	if (ret == -2)
		return 2;
	if (ret < 0)
		return 3;

	this->txFrame.Address = this->id;
	this->txFrame.Code = 4;
	this->txFrame.regLength = this->rxFrame.regLength;
	this->txFrame.data[2] = this->rxFrame.regLength * 2;

	
	for (int i = 0; i < this->rxFrame.regLength; i++)
	{
		this->txFrame.SetReg(i,this->RegInputs[ret].Reg[this->rxFrame.regAddr + i- this->RegInputs[ret].Addr0]);
	}

	return 0;
}
//处理读取保持寄存器 0 正确 1 非法地址 2非法长度
int ModbusSlaveLink::dealRegHoildRead(uint16_t addr, uint16_t len)
{
	int ret = this->searchRegHoildGroup(addr, len);
	if (ret == -1)
		return 1;
	if (ret == -2)
		return 2;
	if (ret < 0)
		return 3;
	this->txFrame.Address = this->id;
	this->txFrame.Code = 3;
	this->txFrame.regLength = this->rxFrame.regLength;
	this->txFrame.data[2] = this->rxFrame.regLength * 2;
	for (int i = 0; i < this->rxFrame.regLength; i++)
	{
		this->txFrame.SetReg(i, this->RegHoildings[ret].Reg[this->rxFrame.regAddr + i - this->RegHoildings[ret].Addr0]);
	}
	return 0;
}
//处理写入保持寄存器 0 正确 1 非法地址 2非法长度
int ModbusSlaveLink::dealRegHoildWrite(uint16_t addr, uint16_t len)
{
	int ret = this->searchRegHoildGroup(addr, len);
	if (ret == -1)
		return 1;
	if (ret == -2)
		return 2;
	if (ret < 0)
		return 3;

	uint16_t tt;
	debug_printf("\nWriteMultipleRegisters reg:%d len:%d\n", addr, len);

	for (int i = 0; i < this->rxFrame.regLength; i++)
	{
		tt = this->rxFrame.data[i * 2 + 7];
		tt <<= 8;
		tt += this->rxFrame.data[i * 2 + 8];
		this->RegHoildings[ret].Reg[this->rxFrame.regAddr + i - this->RegHoildings[ret].Addr0] = tt;
	}
	if (this->OnUpdateRegHoid)
	{
		this->OnUpdateRegHoid(addr, len);
	}

	return 0;
}
//处理写入单个保持寄存器 0 正确 1 非法地址 2非法长度
int ModbusSlaveLink::dealRegHoildWriteOne(uint16_t addr, uint16_t val)
{
	int ret = this->searchRegHoildGroup(addr, 1);
	if (ret == -1)
		return 1;
	if (ret == -2)
		return 2;
	if (ret < 0)
		return 3;
	this->RegHoildings[ret].Reg[addr] = val;
	if (this->OnUpdateRegHoid)
	{
		this->OnUpdateRegHoid(addr, 1);
	}

	return 0;
}
//查找寄存器组，没有查找到返回负值
int ModbusSlaveLink::searchRegInGroup(uint16_t addr, uint16_t len)
{
	for (int i = 0; i < this->RegInputLen; i++)
	{
		if ((addr >= this->RegInputs[i].Addr0) && //起始地址对
			((addr + len) <= (this->RegInputs[i].Addr0 + this->RegInputs[i].Lenth)) && //长度对
			(this->RegInputs[i].Reg!=0)) //寄存器指针不为空
			return i;
	}

	return -1;
}
//查找保持寄存器组，没有查找到返回负值
int ModbusSlaveLink::searchRegHoildGroup(uint16_t addr, uint16_t len)
{
	for (int i = 0; i < this->RegHoildingLen; i++)
	{
		if ((addr >= this->RegHoildings[i].Addr0) && //起始地址对
			((addr + len) <= (this->RegHoildings[i].Addr0 + this->RegHoildings[i].Lenth)) && //长度对
			(this->RegHoildings[i].Reg != 0)) //寄存器指针不为空
			return i;
	}

	return -1;
}
