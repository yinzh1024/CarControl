#ifndef _CAR_CONTROL_H_
#define _CAR_CONTROL_H_

enum CarSpeedControlDirectory
{
	left = 0,
	right
};

enum CarDriveWay
{
	//������
	twoWheel = 2,
	threeWheel,
	fourWheel,
	//������ʽ
	rollWheel = 2, // ������
	motorWheel = 3,// ���
	twoDrive = 2,  // ��������
	fourDrive = 4  // ��������
};

enum CarWheelDirectory
{
	frontMiddle = 0,
	backMiddle,
	frontLeft = 0,
	frontRight,
	backLeft,
	backRight,
};

struct CarWheelRollDirectory
{
	void (*forward)(int gpio);
	void (*backward)(int gpio);
	//������ת���������
	void (*turnLeft)(float turnAngle);
	void (*turnRight)(float turnAngle);
	void (*toMiddle)(void);
};

struct CarSpeedControler
{
	//ȫ�������ʱ��PWMֵ
	int fullPWMValue;
	//ȫ����ת��
	int fullPowerRPM;
	//�ٶȿ��ƺ���, ����Ϊ���ٱ�
	void (*speedControl)(float);
};

struct CarWheel
{
	char *name;
	int gpio;
	//���ӵ�ת���������
	struct CarWheelRollDirectory *rollDirectory;
};

typedef struct Car
{
  //С���ж��ָ���
  int wheelCount;
  //С��������ʽ
  int driveWay;
  //С���ĳ��ֽṹ����
  struct CarWheel *wheel;
  struct CarSpeedControler *speed;
}CarStruct;


extern void TurnLeft(float leftReductionRatio, float rightReductionRadio);
extern void TurnRight(float leftReductionRatio, float rightReductionRadio);
extern int CarRegist(struct Car *car);

#endif
