/****************************************************************************
* ���̴������
* ʹ��ȫ�����±����ͺ���
uint8	KeyFIFO[8];//��ֵѭ������
uint8	KeyPf,KeyPr;//����ͷָ��,��ȡ��ֵʱʹ��
* �����л�ȡ��ֵ��uint8 GetKey(void);void DoKey(void);
ʹ��GetKey(),��õ�5bitΪ��ֵ����3bit��ʾ����״̬��������Ҫ�ж�bit5�жϰ����Ƿ�Ϊ��Ч��������⴦����
	& 0x20; // ��ʾ�˼��Ѿ���������⣬Ϊ��Ч���¡�
	& 0x40; // ��ʾ����ʱ���Ѿ����������жϱ�׼
	& 0x80; // ��ʾ�ѱ�ִ��
	��5bit��ֵ		��Ӧ�İ���
	 0				����Ч������
	 1				��
	 2				1
	 3				4
	 4				7
	 5				help
	 6				��
	 7				2
	 8				5
	 9				8
	10				0
	11				��
	12				3
	13				6
	14				9
	15				F?
	16				��
	17				Enter[��]
	18				Menu [����]
	19				��������
	20              ��Back���ң�
	21				����
	22				����
	23				����
	24				����
* �жϴ���ɨ���״̬void PutKey(void)
* ������ʼ�� void Key_Ini(void)
* FanYF@ynao.ac.cn
****************************************************************************/
// �޸ģ�2008-07-6 ����� ������к���
//		2008-8-25	�����		��Timer0�ж�ʱ����1/32���С��1/100�룬���ԣ�����ȥ�����ͳ���ʱ�䵹��ʱ��Ӧ���ӡ�	
//		2009-6-1	�����		�������,ȥ��2����Ч����ͬʱ���º�1��������֮����ɵ��ް���״̬��	




#define KEYQD 0x09//��ȥ���ж�ʱ�䣬2008-8-30��PLL��Ƶ������3��
#define KEYCA 0xC0//�������ж�ʱ�䣬2008-8-30��PLL��Ƶ������3��
#define KEYMASK 0x72400000 // 0b01110010010000000000000000000000
uint8	KeyFIFO[8];//��ֵѭ������
uint8	KeyPf,KeyPr;//����ͷָ��,��ȡ��ֵʱʹ��
	//����βָ��,�洢��ֵʱʹ��
	
uint8 
	KeyTime,//ɨ�������ʱ��	;
	KeyDirTime;//ɨ��ڶ����������ʱ��		// FanYF 20090601	�������
uint8
	KeyChar,//ɨ���ֵ�ֽڸ�ʽ��(��ִ�У��ܼ���������ȥ����4bit��ֵ)��0��ʾ�޼�����
	KeyDir;				// FanYF 20090601	�������
/****************************************************************************
* ���ƣ�GetKey()
* ���ܣ���ȡɨ�����ֵ��
* ��ڲ�������
* ���ڲ���������������һ�ΰ�����ֵ����״̬��
****************************************************************************/
uint8 GetKey(void)
{
	// ������в��գ�˵����δִ�еļ�����Ӷ��ж�ȡ�ü�
	// ������пգ��򷵻ص�ǰ�İ������
	// ���ظ�ʽͬKeyChar��ʽ��(��ִ�У���������ȥ����5bit��ֵ)��
	// 		���Ϊ0����ʾû�м������¡�
	if(KeyPf == KeyPr)// ���п�
	{	
		return(KeyChar);
	}
	else// ���в���
	{
		return(KeyFIFO[KeyPf]);
	}
}
/****************************************************************************
* ���ƣ�DoKey()
* ���ܣ������ȡ��ɨ����󣬴�KeyFIFO�����С�
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void DoKey(void)
{
	// ��ִ�м������FIFO���գ�ʹ�øú�������ֵ��FIFO
	// ���FIFO�գ����ǵ�ǰ���ѱ�ִ�С�
	if(KeyPf == KeyPr)// ���п�
	{	
		KeyChar |= 0x80;
	}
	else// ���в���
	{
		KeyPf = (KeyPf + 1) % 8;
	}
}
/****************************************************************************
* ���ƣ�PutKey()
* ���ܣ�3msһ�Σ�T0�жϣ����̶�ȡ���õ����ܼ�����ʱ���ɨ���״̬��
* ��ڲ�������
* ���ڲ��������ܼ�����ʱ���ɨ���״̬
****************************************************************************/

void PutKey(void)
{
	uint8	col,raw,raw_o,num,dir,key;
		//�����µ���
		//�����µ���
		//ɨ�������
		//������
		//�����������
		//��ֵ
	uint32	pin0tmp;
	//�ж�ɨ�����
//	IOCLR0 = (KEY1 | KEY2 | KEY3 | KEY4 | KEY5);
	num = 0;//����������״̬
	raw = 0;
	col = 0;
	dir = 0;
	for(raw_o=0;raw_o<4;raw_o++)  // ɨ��ABCD��
	{
		IOSET1 = (KEYA | KEYB | KEYC | KEYD);
		IODIR1	= 0x03C00000;
		IODIR1 |= (1<<19) >> raw_o;//ɨ����� ����KeyA,B,C,D
		IOCLR1 = (1<<19) >> raw_o;//ɨ����� ����KeyA,B,C,D
		if ( (IOPIN0 & KEYMASK) ^ KEYMASK )
		{
			pin0tmp = IOPIN0;	// ��ȡKey1��2��3��4��5��ƽ
			if(!(pin0tmp & KEY1))	// �����
			{
				col = 1;
				key = raw;// ����key����������ͬʱ����2�������ʱ�ļ�ֵ
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
	if(num==0) key =0; // ���㲻���ļ�ֵ
	else if(num==1) key = raw * 5 + col;// �����һ�������µļ�ֵ
	else if((num==2)&&(dir==2))	// ���㰴��2������Ч�����ʱ�ļ�ֵ��key��ŵ�һ������raw��ŵڶ�������
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
	else key = 0x00;	// ����2�����ϰ�������Ϊ��Ч
	if(key)//����Ч������ ������Ч������⣬������1��������
	{
		if((KeyChar & 0x1f) == key)//����������ͬ��	������ȥ�����ͳ������
		{
			if(KeyTime > KEYQD) KeyChar |= 0x20;
			if(KeyTime > KEYCA) KeyChar |= 0x40;
			if(KeyTime < 0xff) KeyTime++;
		}
/*	 1				��
	 6				��
	11				��
	16				��
	21				����
	22				����
	23				����
	24				����
	// FanYF 20090601	�������
*/
		else if((KeyChar & 0x1f) >= 21)// �ϴΰ��·�����ϼ�
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

		else if( dir == 2)//���ΰ�2����
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
			KeyDir = 0;		   // FanYF 20090601	�������
			KeyDirTime = 0;		 // FanYF 20090601	�������
			KeyTime = 0;
		}
	}
	else//û�м����� ���������ϴΰ����ձ��ͷ�
	{
		if((KeyChar & 0x20) && !(KeyChar & 0x80))//�ϴμ�⵽��Ч�����£����ձ��ͷţ��Ҽ�δ��ִ�У��������
		{
			if(!(((KeyPr+1) % 8) == KeyPf))//����δ���������
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

