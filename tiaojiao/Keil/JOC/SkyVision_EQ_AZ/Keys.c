/****************************************************************************
* 键盘处理程序
* 使用全局以下变量和函数
uint8	KeyFIFO[8];//键值循环队列
uint8	KeyPf,KeyPr;//队列头指针,读取键值时使用
* 程序中获取键值：uint8 GetKey(void);void DoKey(void);
使用GetKey(),获得低5bit为键值，高3bit表示按键状态。至少需要判断bit5判断按键是否为有效（抖动检测处理）。
	& 0x20; // 表示此键已经过抖动检测，为有效按下。
	& 0x40; // 表示按下时间已经超过长按判断标准
	& 0x80; // 表示已被执行
	低5bit键值		对应的按键
	 0				无有效键按下
	 1				左
	 2				1
	 3				4
	 4				7
	 5				help
	 6				下
	 7				2
	 8				5
	 9				8
	10				0
	11				右
	12				3
	13				6
	14				9
	15				F?
	16				上
	17				Enter[黄]
	18				Menu [绿左]
	19				［照明］
	20              红Back［右］
	21				左下
	22				左上
	23				右下
	24				右上
* 中断处理扫描键状态void PutKey(void)
* 开机初始化 void Key_Ini(void)
* FanYF@ynao.ac.cn
****************************************************************************/
// 修改：2008-07-6 范玉峰 完成所有函数
//		2008-8-25	范玉峰		因Timer0中断时间由1/32秒减小到1/100秒，所以，按键去抖动和长按时间倒计时相应增加。	
//		2009-6-1	范玉峰		调方向键,去掉2个有效方向同时按下和1个方向按下之间过渡的无按键状态。	




#define KEYQD 0x09//键去抖判断时间，2008-8-30因PLL倍频，增加3倍
#define KEYCA 0xC0//键长按判断时间，2008-8-30因PLL倍频，增加3倍
#define KEYMASK 0x72400000 // 0b01110010010000000000000000000000
uint8	KeyFIFO[8];//键值循环队列
uint8	KeyPf,KeyPr;//队列头指针,读取键值时使用
	//对列尾指针,存储键值时使用
	
uint8 
	KeyTime,//扫描键按下时间	;
	KeyDirTime;//扫描第二方向键按下时间		// FanYF 20090601	调方向键
uint8
	KeyChar,//扫描键值字节格式：(已执行，窜键，长按，去抖，4bit键值)，0表示无键按下
	KeyDir;				// FanYF 20090601	调方向键
/****************************************************************************
* 名称：GetKey()
* 功能：获取扫描键盘值。
* 入口参数：无
* 出口参数：队列中最先一次按键键值（含状态）
****************************************************************************/
uint8 GetKey(void)
{
	// 如果队列不空，说明有未执行的键，则从队列读取该键
	// 如果对列空，则返回当前的按键情况
	// 返回格式同KeyChar格式：(已执行，长按，已去抖，5bit键值)，
	// 		如果为0，表示没有键被按下。
	if(KeyPf == KeyPr)// 队列空
	{	
		return(KeyChar);
	}
	else// 队列不空
	{
		return(KeyFIFO[KeyPf]);
	}
}
/****************************************************************************
* 名称：DoKey()
* 功能：处理读取的扫描键后，从KeyFIFO出队列。
* 入口参数：无
* 出口参数：无
****************************************************************************/
void DoKey(void)
{
	// 当执行键后，如果FIFO不空，使用该函数将键值出FIFO
	// 如果FIFO空，则标记当前键已被执行。
	if(KeyPf == KeyPr)// 队列空
	{	
		KeyChar |= 0x80;
	}
	else// 队列不空
	{
		KeyPf = (KeyPf + 1) % 8;
	}
}
/****************************************************************************
* 名称：PutKey()
* 功能：3ms一次（T0中断）键盘读取，得到功能键按下时间和扫描键状态。
* 入口参数：无
* 出口参数：功能键按下时间和扫描键状态
****************************************************************************/

void PutKey(void)
{
	uint8	col,raw,raw_o,num,dir,key;
		//被按下的列
		//被按下的行
		//扫描行输出
		//按键数
		//方向键按键数
		//键值
	uint32	pin0tmp;
	//判断扫描键。
//	IOCLR0 = (KEY1 | KEY2 | KEY3 | KEY4 | KEY5);
	num = 0;//清零多键按下状态
	raw = 0;
	col = 0;
	dir = 0;
	for(raw_o=0;raw_o<4;raw_o++)  // 扫描ABCD线
	{
		IOSET1 = (KEYA | KEYB | KEYC | KEYD);
		IODIR1	= 0x03C00000;
		IODIR1 |= (1<<19) >> raw_o;//扫描输出 依次KeyA,B,C,D
		IOCLR1 = (1<<19) >> raw_o;//扫描输出 依次KeyA,B,C,D
		if ( (IOPIN0 & KEYMASK) ^ KEYMASK )
		{
			pin0tmp = IOPIN0;	// 读取Key1，2，3，4，5电平
			if(!(pin0tmp & KEY1))	// 方向键
			{
				col = 1;
				key = raw;// 借用key变量，计算同时按下2个方向键时的键值
				raw = raw_o;
				num++;
				dir++;
			}
			if(!(pin0tmp & KEY2))
			{
				col = 2;
				raw = raw_o;
				num++;
			}
			if(!(pin0tmp & KEY3))
			{
				col = 3;
				raw = raw_o;
				num++;
			}
			if(!(pin0tmp & KEY4))
			{
				col = 4;
				raw = raw_o;
				num++;
			}
			if(!(pin0tmp & KEY5))
			{
				col = 5;
				raw = raw_o;
				num++;
			}
		}
	}
	if(num==0) key =0; // 计算不按的键值
	else if(num==1) key = raw * 5 + col;// 计算仅一个键按下的键值
	else if((num==2)&&(dir==2))	// 计算按下2个键有效方向键时的键值，key存放第一个方向，raw存放第二个方向
	{
		switch(key)
		{
			case 0:
				if(raw==1) key = 21;
				else if(raw==3) key = 22 ;
				else key = 0;
				break;
			case 1:
				if(raw==2) key = 23;
				else key = 0;
				break;
			case 2:
				if(raw==3) key = 24;
				else key = 0;
				break;
			default:
				break;
		}
	}
	else key = 0x00;	// 按下2个以上按键，视为无效
	if(key)//有有效键按下 （除有效方向键外，仅按下1个按键）
	{
		if((KeyChar & 0x1f) == key)//持续按下相同键	，进行去抖动和长按检测
		{
			if(KeyTime > KEYQD) KeyChar |= 0x20;
			if(KeyTime > KEYCA) KeyChar |= 0x40;
			if(KeyTime < 0xff) KeyTime++;
		}
/*	 1				左
	 6				下
	11				右
	16				上
	21				左下
	22				左上
	23				右下
	24				右上
	// FanYF 20090601	调方向键
*/
		else if((KeyChar & 0x1f) >= 21)// 上次按下方向组合键
		{
			switch(KeyChar & 0x1f)
			{	
				case 21:
					if((key == 1)||(key == 6)) KeyChar = (KeyChar & 0xe0 | key);
					break;
				case 22:
					if((key == 1)||(key == 16))KeyChar = (KeyChar & 0xe0 | key);
					break;
				case 23:
					if((key == 11)||(key == 6))KeyChar = (KeyChar & 0xe0 | key);
					break;
				case 24:
					if((key == 11)||(key == 16))KeyChar = (KeyChar & 0xe0 | key);
					break;
				default:
					break;
			}
		}

		else if( dir == 2)//本次按2方向
		{
			if(KeyDir == key)
			{
				if(KeyDirTime > KEYQD) KeyChar = (KeyChar & 0xe0 | key);
				if(KeyDirTime < 0xff) KeyDirTime++;
			}
			else 
			{
				KeyDir = 0;
				switch(KeyChar & 0x1f)
				{	
					case 1:
						if((key == 21)||(key == 22))KeyDir=key;
						break;
					case 6:
						if((key == 21)||(key == 23))KeyDir=key;
						break;
					case 11:
						if((key == 23)||(key == 24))KeyDir=key;
						break;
					case 16:
						if((key == 22)||(key == 24))KeyDir=key;
						break;
					default:
						break;
				}
			}
		}
		else{
			KeyChar = key;
			KeyDir = 0;		   // FanYF 20090601	调方向键
			KeyDirTime = 0;		 // FanYF 20090601	调方向键
			KeyTime = 0;
		}
	}
	else//没有键按下 ，可能是上次按键刚被释放
	{
		if((KeyChar & 0x20) && !(KeyChar & 0x80))//上次检测到有效键按下（键刚被释放）且键未被执行，则入队列
		{
			if(!(((KeyPr+1) % 8) == KeyPf))//队列未满，入队列
			{
				KeyFIFO[KeyPr] = KeyChar;
				KeyPr = (KeyPr + 1) % 8;
			}
		}
		KeyChar = 0;
		KeyTime = 0;
	}
}

void Key_Ini(void)
{
	KeyTime=0;
	KeyPf=KeyPr=0;
	KeyChar = 0;
}

