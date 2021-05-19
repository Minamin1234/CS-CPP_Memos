//HT21A099 Minami Riku
// "BounBall"(BoundBall)
//HT21A099.cpp
//����������ł���{�[����ł��Ԃ��Ƃ����Q�[���B��i��Q�i�{�[����ł��Ԃ��Q�[���j���Q�l�ɍ\�z�����Q�[���B
//���̍�i�̖ʔ����Ƃ���͍����̕ǂŒ��˕Ԃ��Ă���̂ł͂Ȃ��A�����ɔ��ōs������A�{�[���̔��˂���鑬�x�A�p�x�������_���ɐݒ肳��āA
// ���ŗ���̂Ń{�[���̋O�����\�����Â炭�A����Ӗ��ʔ����Q�[���ƂȂ��Ă���B
//�u//GameSettings�v�ɂ���ϐ��������鎖�ɂ���āA�Q�[���̓�Փx��ς��邱�Ƃ��ł��A�Q�[���Ń`�[�g�����Ă��銴�o���y���߂�B
//�E�B���h�E�̏㉺���{�[���̒��˕Ԃ�̕ǂƂȂ��Ă���A���̃E�B���h�E�̑傫����ς��鎖���ł��ĐF��ȓ�Փx�ŃQ�[���ɒ��킷�邱�Ƃ��ł���B

//�{�[���̐����������ꍇ�̓N���X�����č\�z���čs���ق���������������Ȃ��B
//(�{�[���̐���������ɂ�āA�R�[�h�̗ʂ��c��ɂȂ��Ă���)
#include <t-pro1.h>

//�w�肳�ꂽ�͈͂ŕ������܂ރ����_���Ȑ���Ԃ��֐�
double Get_Random_Sighned_InRange(double Range)
{
    double Current = rand() % (int)(Range * 2) + 1;
    if (Current >= Range)
    {
        Current = Current - Range;
    }
    else if (Current < Range)
    {
        Current = -Current;
    }

    return Current;
}

//�w�肳�ꂽ�͈͂Ń����_���Ȑ���Ԃ��֐��i�����Ȃ��j
double Get_Random_InRange(double Range)
{
    double Current = rand() % (int)Range + 1;
    return Current;
}

//�w�肳�ꂽ�ŏ��l�E�ő�l�͈̔͂Ń����_���Ȑ���Ԃ��֐��i�����Ȃ��j
double Get_Random_InRange(double Range_Min, double Range_Max)
{
    double Current = (rand() % (int)Range_Max + 1) + Range_Min;
    if (Current > Range_Max)
    {
        Current = Current - Range_Min;
    }
    return Current;
}

//0�`�P�͈̔͂Ń����_���Ȑ���Ԃ��֐�
double Get_Random_Number()
{
    double Current = rand() % 2;
    return Current;
}

//�x���烉�W�A���ɕϊ�����֐�
double Get_Radian_FromDegree(double Rotation)
{
    double Current = Rotation * M_PI / 180;
    return Current;
}

//GrobalVariables�@//�֐��O����ł��A�N�Z�X�ł���ϐ� //�ϐ��̃R�����g�����Ɂu//Do not change�v�ƕ\�L����Ă���ϐ��̒l�͕ύX���Ȃ��ł��������B�Q�[���̋����ɉe�����o�܂��B

//GameSettings
//WindowSettings�@//�E�B���h�E�̐ݒ�

string Window_Name = "Game";//�E�B���h�E�̃^�C�g��
int Window_Width = 1500;//�E�B���h�E�̕�
int Window_Height = 900;//�E�B���h�E�̍���

int WindowFrame_X = Window_Width / 5;//X���W�̍ő�l�@//Do not change
int WindowFrame_Y = Window_Height / 5;//Y���W�̍ő�l�@//Do not change


//ShowingString...SS�@//��ʏ�ɕ\������镶���̐ݒ�

double SS_Location_X = -WindowFrame_X + 20;//�X�R�A�����\�������ʒu�̂w���W
double SS_Locaiton_Y = WindowFrame_Y - 20;//�X�R�A�����\�������ʒu�̂x���W
double SS_Size = 50;//�X�R�A���̕����T�C�Y
double SS_Rotation = 0;//�X�R�A���̉�]

//Player...Plane�@//�ł��Ԃ��̐ݒ�


double Plane_Location_X = WindowFrame_X - 25;//�̈ʒu�̂w���W�@//�x���W�̓}�E�X�ɂ���ē������̂Őݒ肵�Ă��Ȃ��@//�E�B���h�E�̉E�[����Q�T�P�ʂ��炵���ʒu
double Plane_Size_X = 10;//�̕�
double Plane_Size_Y = 100;//�̍���

//ScoreSetting�@//�X�R�A�̓_�̐ݒ�
int TimeLimit_Second = 60;//���Ԑ���

int CurrentTime = clock() / 1000;//���݂̌o�߂����b���@//Do not change

int CurrentScore = 0;//���݂̃X�R�A
int AddScore_Min = 50;//�ł��Ԃ��ɐ��������Ƃ��Ƀ����_���ɕt�^�����X�R�A�̍ŏ��l
int AddScore_Max = 150;//�ł��Ԃ��ɐ��������Ƃ��Ƀ����_���ɕt�^�����X�R�A�̍ő�l
int Deduction_Min = 50;//�ł��Ԃ��Ɏ��s�����Ƃ��Ƀ����_���Ɍ��_�����X�R�A�̍ŏ��l
int Deduction_Max = 100;//�ł��Ԃ��Ɏ��s�����Ƃ��Ƀ����_���Ɍ��_�����X�R�A�̍ő�l

//Ball�@//�v���C���[���ł��Ԃ��{�[���A���ł���{�[���̐ݒ�
double Ball_Location_X = -WindowFrame_Y;//�{�[���̈ʒu�QX�@//Do not change

double Ball_Location_Y = 0;//�{�[���̈ʒu�QY
double Ball_Radius = 25;//�{�[���̔��a
double Ball_SpeedRange_Max = 15;//�{�[�����ł��o����郉���_���ȃX�s�[�h�̍ő�l(�����l) //�����̒l���グ��ƍł������{�[�������˂����悤�ɂȂ�
double Ball_SpeedRange_Min = Ball_SpeedRange_Max - 5;//�{�[�����ł��o����郉���_���ȃX�s�[�h�̍ŏ��l�i�����l�j//�ő�l����������l���ŏ��l�Ƃ��Ă���@
                                                     //���̒l��������ƒx���{�[���͔��˂���Ȃ��Ȃ��Ă���B
                                                     //���Ӂj�ő�l���傫���l�ɐݒ肵�Ȃ��ł��������B
                                                     //�K���A����(Ball_SpeedRange_Min < Ball_SpeedRange_Max)�𖞂����B

double Ball_CurrentSpeed = Get_Random_InRange(Ball_SpeedRange_Min, Ball_SpeedRange_Max);//�{�[���̌��݂̑��x //Do not change
double Ball_CurrentDirection = 1;//���ł����{�[���̕����i�P�E�E�E�������j //Do not change

double Ball_Rotation = 90;//�{�[���̉�]�i�~�ł͂��邪�A�ł��o�����p�x���ω�����j(�����l)
double Ball_Rotarion_RangeMin = Ball_Rotation - 10;//�{�[�����ł��o����郉���_���Ȋp�x�̍ŏ��l //(�����ł͏����l��+- 10���Ă��܂�)
double Ball_Rotation_RangeMax = Ball_Rotation + 10;//�{�[�����ł��o����郉���_���Ȋp�x�̍ő�l //��Ɠ��l

double Ball_Direction_X = 0;//�{�[���̊p�x�x�N�g��X�����@//Do not change
double Ball_Direction_Y = 1;//�{�[���̊p�x�x�N�g��Y�����@//Do not change
bool IsSpawned = false;//�{�[���͏o�����Ă��邩�@//Do not change
bool IsBlocked = false;//�{�[���͑ł��Ԃ��ꂽ���i�Ƀu���b�N���ꂽ���j//Do not change

//Value Changing //���Ԍo�߂ƂƂ��ɕω�����l�Ɋւ���ϐ�

////Plane(Player)
double AmountOf_Plane_Size_Height = 0.01;//���Ԍo�߂ƂƂ��ɑ�������̍����̌�����
bool Plane_Size_Height_IsStatic = true;//�̍����͎��Ԍo�߂ƂƂ��Ɍ��������Ȃ���
double Min_Plane_Height = 5;//��������̍����̍ŏ��l(�����ł̓{�[���̍ŏ��l�ƈ�v�����Ă��܂��B)

////Ball
double AmountOf_Ball_Radius = 0.01;//���Ԍo�߂ƂƂ��ɑ�������{�[�����a�̑�����
bool Ball_Radius_IsStatic = true; //�{�[���̔��a�͎��Ԍo�߂ƂƂ��ɕω������Ȃ���
double AmountOf_Ball_Speed_Range_Max = 0.01;//���Ԍo�߂ƂƂ��ɑ������郉���_���ȃ{�[�����x�̍ő�l�̑����ʁ@//�����_���ɕԂ����͈͂̍ő�l���������Ă���
double AmountOf_Ball_Speed_Range_Min = 0.005;//���Ԍo�߂ƂƂ��ɑ������郉���_���ȃ{�[�����x�̍ŏ��l�̑����ʁ@//���X�Ƀ����_���ɕԂ����ŏ��l���オ���Ă���
bool Ball_SpeedRange_IsStatic = true;//�����_���ɕԂ����{�[�����x�͈͕̔͂ω������Ȃ���
double Min_Ball_Radius = Min_Plane_Height;//�ω�����{�[�����a�̍ŏ��l
double Max_Ball_Speed_Range_Min = Ball_SpeedRange_Min + 10;//�������郉���_���ȃ{�[�����x�͈̔͂̍ŏ��l�̍ő�l(�����ł͏����l��10�����������l���ő�l)
double Max_Ball_Speed_Range_Max = Ball_SpeedRange_Max + 15;//�������郉���_���ȃ{�[�����x�͈̔͂̍ő�l�̍ő�l(�����ł͏����l��13�����������l���ő�l)

//Event�@
void AddScore()//�{�[�����ɂ������đł��Ԃ��ɐ��������Ƃ��A���_����C�x���g
{
    if (IsBlocked != true)
    {
        CurrentScore += Get_Random_InRange(AddScore_Min, AddScore_Max);
    }
}

void Missed()//�{�[���̑ł��Ԃ��Ɏ��s�����Ƃ��A���_����C�x���g
{
    if (IsBlocked != true)
    {
        CurrentScore -= Get_Random_InRange(Deduction_Min, Deduction_Max);
    }
}



//Main
void draw()
{
    

    gsetnonblock(ENABLE);//�L�[�̓��͑҂��͂��܂���
    winname(win, Window_Name);//�E�B���h�E�̃^�C�g����ݒ肵�܂�
    gresize(win, Window_Width, Window_Height);//�E�B���h�E�̃T�C�Y��ݒ肵�܂�
    window(win, -WindowFrame_X, -WindowFrame_Y, WindowFrame_X, WindowFrame_Y);//���W�n��ݒ肵�܂��B// wineggx�̃w�b�_�[�t�@�C���̒�`����
    //�ݒ肵���E�B���h�E�T�C�Y��1/5�����W�̍ő�l�ɂȂ�͗l�B����ō��̂Ƃ���A��肭�����Ă���̂�1/5���̗p���Ă��܂��B
    

    Ball_Rotation = Get_Random_InRange(Ball_Rotarion_RangeMin, Ball_Rotation_RangeMax);

    Ball_Direction_X = 0 * cos(Ball_Rotation * M_PI / 180) + 1 * sin(Ball_Rotation * M_PI / 180);//�{�[���̉�]�i�p�x�j��������x�N�g������]������
    Ball_Direction_Y = -0 * sin(Ball_Rotation * M_PI / 180) + 1 * cos(Ball_Rotation * M_PI / 180);//���l��Y���W
    


    layer(win, 0, 1);
    for (;;)
    {
        
        
        if (Ball_Radius <= Min_Ball_Radius)//���Ԍo�߂ƂƂ��Ɍ������Ă����{�[���̔��a���ŏ��l�ɒB������
        {
            //����ȏ�͌��������܂���
        }
        else
        {
            if (Ball_Radius_IsStatic != true)//�{�[���̔��a�����Ԍo�߂ƂƂ��ɕω�������Ƃ�
            {
                Ball_Radius -= AmountOf_Ball_Radius;//���X�Ƀ{�[���̔��a�����������܂�
            }
        }

        if (Ball_SpeedRange_Max >= Max_Ball_Speed_Range_Max)//�����_���ȃ{�[�����x�͈̔͂̍ő�l���ω��̍ő�l�ɒB������
        {
            //����ȏ�͑��������܂���
        }
        else
        {
            if (Ball_SpeedRange_IsStatic != true)//�{�[���̃����_���ɕԂ���鑬�x�͈̔͂�ω�������Ƃ�
            {
                Ball_SpeedRange_Max += AmountOf_Ball_Speed_Range_Max;//�{�[���̃����_���ɕԂ���鑬�x�͈̔͂̍ő�l�𑝉�������
            }
            
        }

        if (Ball_SpeedRange_Min >= Max_Ball_Speed_Range_Min)//�����_���ɕԂ����{�[�����x�͈̔͂̍ŏ��l�����x�l�ɒB������
        {
            //����ȏ㑝�������܂���
        }
        else//�B���Ă��Ȃ��Ƃ�
        {
            if (Ball_SpeedRange_IsStatic != true)//�����_���ɕԂ����{�[���̔��ˑ��x�͈̔͂�ύX����Ƃ��i�ے�u���ˑ��x�͈̔͂̕ύX�͂��Ȃ��iStatic�j�v�̂ł͂Ȃ��j
            {
                Ball_SpeedRange_Min += AmountOf_Ball_Speed_Range_Min;//�{�[���̃����_���ɕԂ���鑬�x�͈̔͂̍ŏ��l�𑝉�������@//�����x�̒x���{�[���͑ł��o����Ȃ��Ȃ��Ă���
            }
            
        }

        if (Plane_Size_Y <= Min_Plane_Height)//�̍����̌������ŏ��l�ɂȂ����Ƃ�
        {
            //����ȏ㌸�������܂���
        }
        else
        {
            if (Plane_Size_Height_IsStatic != true)//�̍����͐ÓI�i�ύX���Ȃ��j�ł͂Ȃ����i�̍�����ύX����Ƃ��j
            {
                Plane_Size_Y -= AmountOf_Plane_Size_Height;//���X�ɔ̍������k�߂Ă���
            }
        }
        

        gclr(win);//���ƂŐݒ肳��Ă����i�q��̃O���b�h�͕`�悵�܂���
        CurrentTime = clock() / 1000;//���݂̎��ԁi�b�j�@//clock()�ŕԂ����l�̓~���b�Ȃ̂�1000ms = 1s
        if (windowId == 0)//�E�B���h�E���t�H�[�J�X����Ă���Ƃ��i�E�B���h�E���ɃJ�[�\�������鎞�j
        {
            if (IsSpawned == true)//�{�[�����o������Ă���Ȃ�΁A�{�[�����`�悳���Ȃ��
            {
                Ball_Location_X += (Ball_Direction_X * Ball_CurrentSpeed) * Ball_CurrentDirection;//�p�x����Z�o���������x�N�g�����X�s�[�h�{���āA���݂̍��W�ɑ����Ă���iX���W�����j
                Ball_Location_Y += (Ball_Direction_Y * Ball_CurrentSpeed) * Ball_CurrentDirection;//�������A�p�x����o���������x�N�g�����X�s�[�h�{���āA���݂̍��W�ɑ����Ă���(Y���W����)

                if (Ball_Location_X - Ball_Radius >= WindowFrame_X || Ball_Location_X + Ball_Radius <= -WindowFrame_X)//�{�[������ʗ��[��ʉ߂��čs������
                {
                    if (Ball_Location_X - Ball_Radius >= WindowFrame_X)//�ɓ����炸�A���̂܂܉�ʉE����ʉ߂��čs������
                    {
                        Missed();//�~�X����
                    }

                    IsSpawned = false; //�{�[���������܂��i�`�悳��Ȃ����܂��j
                }

                if (Ball_Location_Y + Ball_Radius >= WindowFrame_Y || Ball_Location_Y - Ball_Radius <= -WindowFrame_Y)//��ʂ̏㉺�̉��ɓ���������
                {
                    Ball_Direction_Y = -Ball_Direction_Y;//�����x�N�g����Y�����𔽓]�����܂��B(����)
                }

                if (Ball_Location_X + Ball_Radius >= Plane_Location_X)//�{�[�����ɓ���������
                {
                    if (Ball_Location_Y + Ball_Radius <= mouseY + (Plane_Size_Y / 2) && Ball_Location_Y + Ball_Radius >= mouseY - (Plane_Size_Y / 2))//�Ƀ{�[���̏㔼���œ���������
                    {
                        AddScore();//���_���܂�
                        IsBlocked = true;//�{�[���͔ɂ���ău���b�N����A���˕Ԃ��ꂽ
                        Ball_CurrentDirection = -1;//�S�ʓI�Ƀ{�[���̉^�������͋t�����ɂȂ�
                    }
                    else if (Ball_Location_Y - Ball_Radius <= mouseY + (Plane_Size_Y / 2) && Ball_Location_Y - Ball_Radius >= mouseY - (Plane_Size_Y / 2))//�Ƀ{�[���̉������œ���������
                    {
                        AddScore();//���_���܂�
                        IsBlocked = true;//�{�[���͔ɂ���ău���b�N����A���˕Ԃ���܂���
                        Ball_CurrentDirection = -1;//�������A�{�[���̉^�������͋t�ɂ���
                    }
                }
            }
            else//�i��ʊO�ɔ��ōs���Ă��܂����Ȃǂ̗��R�Łj�{�[�����o������Ȃ��Ȃ�����
            {
                //�{�[���̏������������Ă��܂�
                Ball_Rotation = Get_Random_InRange(Ball_Rotarion_RangeMin, Ball_Rotation_RangeMax);//�{�[���̉^�������i���ˊp�x�j�͎w�肵���͈͂̒����烉���_���Ɍ��肵�܂��B
                Ball_Direction_X = (0 * cos(Ball_Rotation * M_PI / 180)) + (1 * sin(Ball_Rotation * M_PI / 180));//�����x�N�g���i���K�����ꂽ�j���w�肵���p�x�ŉ�]������B(X��)
                Ball_Direction_Y = -(0 * sin(Ball_Rotation * M_PI / 180)) + (1 * cos(Ball_Rotation * M_PI / 180));//�������AY���ł�
                Ball_CurrentDirection = 1;//�����x�N�g������ŏI�I�ɉ^�����������肷��̂Ɋ|���鐔(-1��+1)(-1�͋t����)
                Ball_Location_X = -WindowFrame_X - Ball_Radius;//�����̃{�[���ʒu
                Ball_Location_Y = Get_Random_Sighned_InRange(WindowFrame_Y - Ball_Radius);//�������A�����Y���W
                Ball_CurrentSpeed = Get_Random_InRange(Ball_SpeedRange_Min,Ball_SpeedRange_Max);//���ݔ��˂���Ă���{�[���̑��x�i�x�N�g���̒����ɂ��Ȃ�j
                IsBlocked = false;//�{�[���͔ɂ���ău���b�N���ꂽ���ǂ����@�u�{�[���̓u���b�N����Ă��܂���v�ɐݒ�
                IsSpawned = true;//�u�{�[���͌��݁A�o������Ă��܂��v�ɐݒ�
            }
            
        }
        else//�E�B���h�E���t�H�[�J�X����Ȃ��Ȃ������i�J�[�\������ʊO�ɍs�������j�j�@//�J�[�\������ʓ��ɖ����Ƃ��̓{�[���̉^�������͍s���܂���B
        {
            newrgbcolor(win, 0, 0, 0);//�����̐F��ݒ�
            drawstr(win, -15, 0, 30, 0, "Paused", "");//������`��iPaused: ���f����Ă���j
        }

        if (TimeLimit_Second - CurrentTime <= 0)//�������Ԃ��O�b�ɂȂ�����
        {
            
            break;//���C�����[�v�𔲂��܂��B�Q�[���i�A�j���[�V�����j�̏I��
        }

        //cout << CurrentScore << endl;
        newrgbcolor(win,0, 0, 255);//�����̐F��ݒ�
        drawstr(win, SS_Location_X, SS_Locaiton_Y, SS_Size, SS_Rotation, "Score: %d",CurrentScore);//�X�R�A��\�����܂�
        drawstr(win, SS_Location_X, SS_Locaiton_Y - 20, SS_Size, SS_Rotation, "Time: %d",TimeLimit_Second - CurrentTime);//�c�莞�Ԃ�\�����܂��B
        newrgbcolor(win, 0, 255, 255);//�̐F��ݒ�
        fillrect(win, Plane_Location_X, mouseY - (Plane_Size_Y / 2), Plane_Size_X, Plane_Size_Y);//��`��@//�}�E�X��Y���W�݂̂Ŕ��㉺������B�@
                                                                                                 //�̒��S�i�����̒��S�j�ɃJ�[�\���������Ă��������̂ŁA�̃T�C�Y�̔����Ɉʒu��ݒ肵��
        newrgbcolor(win, 0, 255, 0);//�{�[���̐F��ݒ�
        fillcirc(win, Ball_Location_X, Ball_Location_Y, Ball_Radius, Ball_Radius);//�h��Ԃ��~��`��
        copylayer(win, 1, 0);
        msleep(10);//10�~���b�A������x�点��B(�����̃y�[�X�𒲐߂���)�@//�ɒ[�ɊԊu���Z���ƃO���t�B�b�N�ɂ�������N����B�B�@//�{�[���̈ړ����x�ɂ��e������
    }

    gclr(win);//�O���b�h�̕`��͍s���܂���
    newrgbcolor(win, 0, 0, 0);//�����̐F��ݒ�i�����j
    drawstr(win, -75, 50, 50, SS_Rotation, "Time UP!!!", "");//�Q�[���I�����̕�������o�́i���Ԑ؂�I�j
    drawstr(win, -75, 0, 50, SS_Rotation, "Your Score: %d", CurrentScore);//�i���Ȃ��̃X�R�A�́Z�Z�_�ł����j
    copylayer(win, 1, 0);
    

}
