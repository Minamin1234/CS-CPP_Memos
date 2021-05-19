//HT21A099 Minami Riku
// "BounBall"(BoundBall)
//HT21A099.cpp
//左側から飛んでくるボールを打ち返すというゲーム。作品例２（ボールを打ち返すゲーム）を参考に構築したゲーム。
//この作品の面白いところは左側の壁で跳ね返ってくるのではなく、左側に飛んで行った後、ボールの発射される速度、角度がランダムに設定されて、
// 飛んで来るのでボールの軌道が予測しづらく、ある意味面白いゲームとなっている。
//「//GameSettings」にある変数をいじる事によって、ゲームの難易度を変えることができ、ゲームでチートをしている感覚も楽しめる。
//ウィンドウの上下がボールの跳ね返りの壁となっており、そのウィンドウの大きさを変える事もできて色んな難易度でゲームに挑戦することができる。

//ボールの数が増えた場合はクラス化して構築して行くほうがいいかもしれない。
//(ボールの数が増えるにつれて、コードの量が膨大になってくる)
#include <t-pro1.h>

//指定された範囲で符号を含むランダムな数を返す関数
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

//指定された範囲でランダムな数を返す関数（符号なし）
double Get_Random_InRange(double Range)
{
    double Current = rand() % (int)Range + 1;
    return Current;
}

//指定された最小値・最大値の範囲でランダムな数を返す関数（符号なし）
double Get_Random_InRange(double Range_Min, double Range_Max)
{
    double Current = (rand() % (int)Range_Max + 1) + Range_Min;
    if (Current > Range_Max)
    {
        Current = Current - Range_Min;
    }
    return Current;
}

//0～１の範囲でランダムな数を返す関数
double Get_Random_Number()
{
    double Current = rand() % 2;
    return Current;
}

//度からラジアンに変換する関数
double Get_Radian_FromDegree(double Rotation)
{
    double Current = Rotation * M_PI / 180;
    return Current;
}

//GrobalVariables　//関数外からでもアクセスできる変数 //変数のコメント末尾に「//Do not change」と表記されている変数の値は変更しないでください。ゲームの挙動に影響が出ます。

//GameSettings
//WindowSettings　//ウィンドウの設定

string Window_Name = "Game";//ウィンドウのタイトル
int Window_Width = 1500;//ウィンドウの幅
int Window_Height = 900;//ウィンドウの高さ

int WindowFrame_X = Window_Width / 5;//X座標の最大値　//Do not change
int WindowFrame_Y = Window_Height / 5;//Y座標の最大値　//Do not change


//ShowingString...SS　//画面上に表示される文字の設定

double SS_Location_X = -WindowFrame_X + 20;//スコア数が表示される位置のＸ座標
double SS_Locaiton_Y = WindowFrame_Y - 20;//スコア数が表示される位置のＹ座標
double SS_Size = 50;//スコア数の文字サイズ
double SS_Rotation = 0;//スコア数の回転

//Player...Plane　//打ち返す板の設定


double Plane_Location_X = WindowFrame_X - 25;//板の位置のＸ座標　//Ｙ座標はマウスによって動かすので設定していない　//ウィンドウの右端から２５単位ずらした位置
double Plane_Size_X = 10;//板の幅
double Plane_Size_Y = 100;//板の高さ

//ScoreSetting　//スコア採点の設定
int TimeLimit_Second = 60;//時間制限

int CurrentTime = clock() / 1000;//現在の経過した秒数　//Do not change

int CurrentScore = 0;//現在のスコア
int AddScore_Min = 50;//打ち返しに成功したときにランダムに付与されるスコアの最小値
int AddScore_Max = 150;//打ち返しに成功したときにランダムに付与されるスコアの最大値
int Deduction_Min = 50;//打ち返しに失敗したときにランダムに減点されるスコアの最小値
int Deduction_Max = 100;//打ち返しに失敗したときにランダムに減点されるスコアの最大値

//Ball　//プレイヤーが打ち返すボール、飛んでくるボールの設定
double Ball_Location_X = -WindowFrame_Y;//ボールの位置＿X　//Do not change

double Ball_Location_Y = 0;//ボールの位置＿Y
double Ball_Radius = 25;//ボールの半径
double Ball_SpeedRange_Max = 15;//ボールが打ち出されるランダムなスピードの最大値(初期値) //ここの値を上げると最も早いボールが発射されるようになる
double Ball_SpeedRange_Min = Ball_SpeedRange_Max - 5;//ボールが打ち出されるランダムなスピードの最小値（初期値）//最大値から引いた値が最小値としている　
                                                     //この値をあげると遅いボールは発射されなくなってくる。
                                                     //注意）最大値より大きい値に設定しないでください。
                                                     //必ず、条件(Ball_SpeedRange_Min < Ball_SpeedRange_Max)を満たす。

double Ball_CurrentSpeed = Get_Random_InRange(Ball_SpeedRange_Min, Ball_SpeedRange_Max);//ボールの現在の速度 //Do not change
double Ball_CurrentDirection = 1;//飛んでいくボールの方向（１・・・正方向） //Do not change

double Ball_Rotation = 90;//ボールの回転（円ではあるが、打ち出される角度が変化する）(初期値)
double Ball_Rotarion_RangeMin = Ball_Rotation - 10;//ボールが打ち出されるランダムな角度の最小値 //(ここでは初期値の+- 10しています)
double Ball_Rotation_RangeMax = Ball_Rotation + 10;//ボールが打ち出されるランダムな角度の最大値 //上と同様

double Ball_Direction_X = 0;//ボールの角度ベクトルX成分　//Do not change
double Ball_Direction_Y = 1;//ボールの角度ベクトルY成分　//Do not change
bool IsSpawned = false;//ボールは出現しているか　//Do not change
bool IsBlocked = false;//ボールは打ち返されたか（板にブロックされたか）//Do not change

//Value Changing //時間経過とともに変化する値に関する変数

////Plane(Player)
double AmountOf_Plane_Size_Height = 0.01;//時間経過とともに増加する板の高さの減少量
bool Plane_Size_Height_IsStatic = true;//板の高さは時間経過とともに減少させないか
double Min_Plane_Height = 5;//減少する板の高さの最小値(ここではボールの最小値と一致させています。)

////Ball
double AmountOf_Ball_Radius = 0.01;//時間経過とともに増加するボール半径の増加量
bool Ball_Radius_IsStatic = true; //ボールの半径は時間経過とともに変化させないか
double AmountOf_Ball_Speed_Range_Max = 0.01;//時間経過とともに増加するランダムなボール速度の最大値の増加量　//ランダムに返される範囲の最大値が増加していく
double AmountOf_Ball_Speed_Range_Min = 0.005;//時間経過とともに増加するランダムなボール速度の最小値の増加量　//徐々にランダムに返される最小値が上がっていく
bool Ball_SpeedRange_IsStatic = true;//ランダムに返されるボール速度の範囲は変化させないか
double Min_Ball_Radius = Min_Plane_Height;//変化するボール半径の最小値
double Max_Ball_Speed_Range_Min = Ball_SpeedRange_Min + 10;//増加するランダムなボール速度の範囲の最小値の最大値(ここでは初期値の10増加させた値が最大値)
double Max_Ball_Speed_Range_Max = Ball_SpeedRange_Max + 15;//増加するランダムなボール速度の範囲の最大値の最大値(ここでは初期値の13増加させた値が最大値)

//Event　
void AddScore()//ボールが板にあたって打ち返しに成功したとき、加点するイベント
{
    if (IsBlocked != true)
    {
        CurrentScore += Get_Random_InRange(AddScore_Min, AddScore_Max);
    }
}

void Missed()//ボールの打ち返しに失敗したとき、減点するイベント
{
    if (IsBlocked != true)
    {
        CurrentScore -= Get_Random_InRange(Deduction_Min, Deduction_Max);
    }
}



//Main
void draw()
{
    

    gsetnonblock(ENABLE);//キーの入力待ちはしません
    winname(win, Window_Name);//ウィンドウのタイトルを設定します
    gresize(win, Window_Width, Window_Height);//ウィンドウのサイズを設定します
    window(win, -WindowFrame_X, -WindowFrame_Y, WindowFrame_X, WindowFrame_Y);//座標系を設定します。// wineggxのヘッダーファイルの定義から
    //設定したウィンドウサイズの1/5が座標の最大値になる模様。それで今のところ、上手くいっているので1/5を採用しています。
    

    Ball_Rotation = Get_Random_InRange(Ball_Rotarion_RangeMin, Ball_Rotation_RangeMax);

    Ball_Direction_X = 0 * cos(Ball_Rotation * M_PI / 180) + 1 * sin(Ball_Rotation * M_PI / 180);//ボールの回転（角度）から方向ベクトルを回転させる
    Ball_Direction_Y = -0 * sin(Ball_Rotation * M_PI / 180) + 1 * cos(Ball_Rotation * M_PI / 180);//同様にY座標
    


    layer(win, 0, 1);
    for (;;)
    {
        
        
        if (Ball_Radius <= Min_Ball_Radius)//時間経過とともに減少していくボールの半径が最小値に達した時
        {
            //これ以上は減少させません
        }
        else
        {
            if (Ball_Radius_IsStatic != true)//ボールの半径を時間経過とともに変化させるとき
            {
                Ball_Radius -= AmountOf_Ball_Radius;//徐々にボールの半径を減少させます
            }
        }

        if (Ball_SpeedRange_Max >= Max_Ball_Speed_Range_Max)//ランダムなボール速度の範囲の最大値が変化の最大値に達した時
        {
            //これ以上は増加させません
        }
        else
        {
            if (Ball_SpeedRange_IsStatic != true)//ボールのランダムに返される速度の範囲を変化させるとき
            {
                Ball_SpeedRange_Max += AmountOf_Ball_Speed_Range_Max;//ボールのランダムに返される速度の範囲の最大値を増加させる
            }
            
        }

        if (Ball_SpeedRange_Min >= Max_Ball_Speed_Range_Min)//ランダムに返されるボール速度の範囲の最小値が限度値に達した時
        {
            //これ以上増加させません
        }
        else//達していないとき
        {
            if (Ball_SpeedRange_IsStatic != true)//ランダムに返されるボールの発射速度の範囲を変更するとき（否定「発射速度の範囲の変更はしない（Static）」のではない）
            {
                Ball_SpeedRange_Min += AmountOf_Ball_Speed_Range_Min;//ボールのランダムに返される速度の範囲の最小値を増加させる　//＝速度の遅いボールは打ち出されなくなってくる
            }
            
        }

        if (Plane_Size_Y <= Min_Plane_Height)//板の高さの減少が最小値になったとき
        {
            //これ以上減少させません
        }
        else
        {
            if (Plane_Size_Height_IsStatic != true)//板の高さは静的（変更しない）ではない時（板の高さを変更するとき）
            {
                Plane_Size_Y -= AmountOf_Plane_Size_Height;//徐々に板の高さを縮めていく
            }
        }
        

        gclr(win);//授業で設定されていた格子状のグリッドは描画しません
        CurrentTime = clock() / 1000;//現在の時間（秒）　//clock()で返される値はミリ秒なので1000ms = 1s
        if (windowId == 0)//ウィンドウがフォーカスされているとき（ウィンドウ内にカーソルがある時）
        {
            if (IsSpawned == true)//ボールが出現されているならば、ボールが描画されるならば
            {
                Ball_Location_X += (Ball_Direction_X * Ball_CurrentSpeed) * Ball_CurrentDirection;//角度から算出した方向ベクトルをスピード倍して、現在の座標に足している（X座標だけ）
                Ball_Location_Y += (Ball_Direction_Y * Ball_CurrentSpeed) * Ball_CurrentDirection;//同じく、角度から出した方向ベクトルをスピード倍して、現在の座標に足している(Y座標だけ)

                if (Ball_Location_X - Ball_Radius >= WindowFrame_X || Ball_Location_X + Ball_Radius <= -WindowFrame_X)//ボールが画面両端を通過して行った時
                {
                    if (Ball_Location_X - Ball_Radius >= WindowFrame_X)//板に当たらず、そのまま画面右側を通過して行った時
                    {
                        Missed();//ミス判定
                    }

                    IsSpawned = false; //ボールを消します（描画されなくします）
                }

                if (Ball_Location_Y + Ball_Radius >= WindowFrame_Y || Ball_Location_Y - Ball_Radius <= -WindowFrame_Y)//画面の上下の縁に当たった時
                {
                    Ball_Direction_Y = -Ball_Direction_Y;//方向ベクトルのY成分を反転させます。(反射)
                }

                if (Ball_Location_X + Ball_Radius >= Plane_Location_X)//ボールが板に当たった時
                {
                    if (Ball_Location_Y + Ball_Radius <= mouseY + (Plane_Size_Y / 2) && Ball_Location_Y + Ball_Radius >= mouseY - (Plane_Size_Y / 2))//板にボールの上半分で当たった時
                    {
                        AddScore();//加点します
                        IsBlocked = true;//ボールは板によってブロックされ、跳ね返された
                        Ball_CurrentDirection = -1;//全面的にボールの運動方向は逆方向になる
                    }
                    else if (Ball_Location_Y - Ball_Radius <= mouseY + (Plane_Size_Y / 2) && Ball_Location_Y - Ball_Radius >= mouseY - (Plane_Size_Y / 2))//板にボールの下半分で当たった時
                    {
                        AddScore();//加点します
                        IsBlocked = true;//ボールは板によってブロックされ、跳ね返されました
                        Ball_CurrentDirection = -1;//同じく、ボールの運動方向は逆にする
                    }
                }
            }
            else//（画面外に飛んで行ってしまったなどの理由で）ボールが出現されなくなった時
            {
                //ボールの情報を初期化しています
                Ball_Rotation = Get_Random_InRange(Ball_Rotarion_RangeMin, Ball_Rotation_RangeMax);//ボールの運動方向（発射角度）は指定した範囲の中からランダムに決定します。
                Ball_Direction_X = (0 * cos(Ball_Rotation * M_PI / 180)) + (1 * sin(Ball_Rotation * M_PI / 180));//方向ベクトル（正規化された）を指定した角度で回転させる。(X軸)
                Ball_Direction_Y = -(0 * sin(Ball_Rotation * M_PI / 180)) + (1 * cos(Ball_Rotation * M_PI / 180));//同じく、Y軸でも
                Ball_CurrentDirection = 1;//方向ベクトルから最終的に運動方向を決定するのに掛ける数(-1か+1)(-1は逆方向)
                Ball_Location_X = -WindowFrame_X - Ball_Radius;//初期のボール位置
                Ball_Location_Y = Get_Random_Sighned_InRange(WindowFrame_Y - Ball_Radius);//同じく、それのY座標
                Ball_CurrentSpeed = Get_Random_InRange(Ball_SpeedRange_Min,Ball_SpeedRange_Max);//現在発射されているボールの速度（ベクトルの長さにもなる）
                IsBlocked = false;//ボールは板によってブロックされたかどうか　「ボールはブロックされていません」に設定
                IsSpawned = true;//「ボールは現在、出現されています」に設定
            }
            
        }
        else//ウィンドウがフォーカスされなくなった時（カーソルが画面外に行った時））　//カーソルが画面内に無いときはボールの運動処理は行いません。
        {
            newrgbcolor(win, 0, 0, 0);//文字の色を設定
            drawstr(win, -15, 0, 30, 0, "Paused", "");//文字を描画（Paused: 中断されている）
        }

        if (TimeLimit_Second - CurrentTime <= 0)//持ち時間が０秒になった時
        {
            
            break;//メインループを抜けます。ゲーム（アニメーション）の終了
        }

        //cout << CurrentScore << endl;
        newrgbcolor(win,0, 0, 255);//文字の色を設定
        drawstr(win, SS_Location_X, SS_Locaiton_Y, SS_Size, SS_Rotation, "Score: %d",CurrentScore);//スコアを表示します
        drawstr(win, SS_Location_X, SS_Locaiton_Y - 20, SS_Size, SS_Rotation, "Time: %d",TimeLimit_Second - CurrentTime);//残り時間を表示します。
        newrgbcolor(win, 0, 255, 255);//板の色を設定
        fillrect(win, Plane_Location_X, mouseY - (Plane_Size_Y / 2), Plane_Size_X, Plane_Size_Y);//板を描画　//マウスのY座標のみで板を上下させる。　
                                                                                                 //板の中心（高さの中心）にカーソルをもっていきたいので、板のサイズの半分に位置を設定した
        newrgbcolor(win, 0, 255, 0);//ボールの色を設定
        fillcirc(win, Ball_Location_X, Ball_Location_Y, Ball_Radius, Ball_Radius);//塗りつぶし円を描画
        copylayer(win, 1, 0);
        msleep(10);//10ミリ秒、処理を遅らせる。(処理のペースを調節する)　//極端に間隔が短いとグラフィックにちらつきが起きる。。　//ボールの移動速度にも影響する
    }

    gclr(win);//グリッドの描画は行いません
    newrgbcolor(win, 0, 0, 0);//文字の色を設定（＝黒）
    drawstr(win, -75, 50, 50, SS_Rotation, "Time UP!!!", "");//ゲーム終了時の文字列を出力（時間切れ！）
    drawstr(win, -75, 0, 50, SS_Rotation, "Your Score: %d", CurrentScore);//（あなたのスコアは〇〇点でした）
    copylayer(win, 1, 0);
    

}
