#include"collision.h"

//---------------------------------
//点と四角の当たり判定
//---------------------------------
bool CheckHitDotToSquare(VECTOR dotPos, VECTOR squarePos,
	int width, int height)
{
	//四角形の上下左右それぞれの座標を計算する
	float up = squarePos.y - height * 0.5f;
	float down = squarePos.y + height * 0.5f;
	float left = squarePos.x - height * 0.5f;
	float right = squarePos.x + height * 0.5f;

	//4つの端をそれぞれチェックして、すべての条件を満たしたらヒット
	if (dotPos.x >= left && dotPos.x <= right
		&& dotPos.y >= up && dotPos.y <= down)
	{
		return true;
	}
	else return false;

}
//矩形同士の当たり判定
bool CheckHitSquareToSquare(VECTOR squarePos1, int width1, int height1, VECTOR squarePos2, int width2, int height2)
{

	//四角形の上下左右それぞれの座標を計算する
	float up1 = squarePos1.y - height1 * 0.5f;
	float down1 = squarePos1.y + height1 * 0.5f;
	float left1 = squarePos1.x - height1 * 0.5f;
	float right1 = squarePos1.x + height1 * 0.5f;

	//四角形の上下左右それぞれの座標を計算する
	float up2 = squarePos2.y - height2 * 0.5f;
	float down2 = squarePos2.y + height2 * 0.5f;
	float left2 = squarePos2.x - height2 * 0.5f;
	float right2 = squarePos2.x + height2 * 0.5f;


	if (up1 <= down2 && down1 >= up2 && left1 <= right2 && right1 >= left2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//円同士の当たり判定
bool CheckHitCircleToCircle(VECTOR circlePos1, int radius1, VECTOR circlePos2, int radius2)
{	//横の長さの二乗を調べる
	float lenX = circlePos1.x - circlePos2.x;
	lenX *= lenX;
	//縦の長さの二乗を調べる
	float lenY = circlePos1.y - circlePos2.y;
	lenY *= lenY;
	//最短距離の二乗を計算
	float len = lenX + lenY;
	//半径二個を足した値の二乗を調べる
	float totalradius = radius1 + radius2;
	totalradius *= totalradius;

	if (len<=totalradius)
	{
		return true;
	}
	else
	{
		false;
	}
	
}
