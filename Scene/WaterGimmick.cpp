#include "WaterGimmick.h"
#include "DxLib.h"

WaterGimmick::~WaterGimmick()
{
	delete floor_;

}

//‰Šú‰»
void WaterGimmick::Initialize()
{
	srand(time(NULL));

	floor_ = new Floor();
	floor_->Initialize();
	//…—¬‰Šú‰»
	InitWaterflow();
	//–A‰Šú‰»
	InitBubble();
}

//…—¬‰Šú‰»
void WaterGimmick::InitWaterflow() {

	//”ÍˆÍ
	this->waterFlowWidth = 200.0f;						//‰¡•
	this->waterFlowHeight = 10.0f;						//c•
	//…—¬‰Šú‰»
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		this->waterFlowTransform[i].x = WIN_WIDTH - waterFlowWidth;		//XÀ•W
		this->waterFlowTransform[i].y = floor_->getMarioFloorpos() - waterFlowHeight;			//YÀ•W
		this->waterFlowTransform[i].radius = 5.0f;		//…—¬–A‚Ì”¼Œa
		this->waterFlowSpeed[i] = 5.0f;			//‘¬“x
		this->waterFlowBright[i] = 255;		//–¾‚é‚³
		this->isActiveWaterFlow[i] = false;		//¶‚«‚Ä‚é‚©
	}
}

//–A‰Šú‰»
void WaterGimmick::InitBubble()
{
	//”ÍˆÍ
	this->bubbleWidth = 200.0f;														//‰¡•
	this->bubbleHeight = WIN_HEIGHT;						//c•
	//–A‰Šú‰»

	this->bubbleTransform.x = bubbleWidth;		//XÀ•W
	this->bubbleTransform.y = bubbleHeight;			//YÀ•W
	this->bubbleTransform.radius = 32.0f;		//…—¬–A‚Ì”¼Œa
	this->bubbleSpeed = 5.0f;			//‘¬“x
	this->isActiveBubble = false;		//¶‚«‚Ä‚é‚©

	//…—¬‚Ì“–‚½‚è”»’è—p
	this->bubbleHit.x = 0.0f;
	this->bubbleHit.y = 0.0f;
	this->bubbleHit.z = 0.0f;

	//–A‚ªo‚éƒ^ƒCƒ~ƒ“ƒO
	this->bubbleCount = 60 * 4;
}

//XV
void WaterGimmick::MarioUpdate(bool& isHitBubble)
{
	//…—¬
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//–AXV
	UpdateBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool& isHitBubble)
{
	//–AXV
	UpdateBubble(isHitBubble);

}

//…—¬XV
void WaterGimmick::UpdateWaterFlow(float floorPos)
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (isActiveWaterFlow[i] == false)
		{
			isActiveWaterFlow[i] = true;
			waterFlowTransform[i].x = WIN_WIDTH;
			waterFlowTransform[i].y = floorPos - waterFlowHeight;
			if (i % 2 == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (isActiveWaterFlow[i] == true)
		{
			waterFlowBright[i] -= 2;
			waterFlowTransform[i].x -= waterFlowSpeed[i];
			waterFlowTransform[i].y -= rand() % 5 - 2;
		}
		if (waterFlowBright[i] <= 0)
		{
			isActiveWaterFlow[i] = false;
			waterFlowBright[i] = 255;
		}
	}
}

//–AXV
void WaterGimmick::UpdateBubble(bool& isHit)
{
	if (bubbleCount <= 0)
	{
		bubbleCount = 0;
		isActiveBubble = true;
	}
	if (isActiveBubble == true)
	{
		if (isHit == false)
		{
			bubbleTransform.y -= bubbleSpeed;
		}

		if (bubbleTransform.y <= 0.0f || isHit == true)
		{
			bubbleTransform.x = bubbleWidth;
			bubbleTransform.y = bubbleHeight;
			isActiveBubble = false;
			isHit = false;
		}
	}
	else
	{
		
		bubbleCount--;
	}


}
//“–‚½‚è”»’è
//“–‚½‚è”»’è—pŠÖ”
void WaterGimmick::IsHitBubble(Transform& transform, bool& isHit)
{
	bubbleHit.x = transform.x - bubbleTransform.x;
	bubbleHit.y = transform.y - bubbleTransform.y;
	bubbleHit.z = bubbleHit.x * bubbleHit.x + bubbleHit.y * bubbleHit.y;
	//–A‚ªo‚Ä‚é‚Æ‚«
	if (isActiveBubble == true && isHit == false)
	{
		//“–‚½‚Á‚Ä‚é‚©
		if (bubbleHit.z <= (bubbleTransform.radius + transform.radius) *
			(bubbleTransform.radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble = false;
		
	}

	DrawFormatString(0, 90, GetColor(255, 255, 255), "bubble::%f,%f,%f", bubbleHit.x, bubbleHit.y, bubbleHit.z);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "pt,bt::%f,%f", transform.y, bubbleTransform.y);
}

//•`‰æ
void WaterGimmick::MarioDraw()
{
	//…—¬•`‰æ
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//–A•`‰æ

	DrawBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount);
}
void WaterGimmick::SonicDraw()
{
	//–A•`‰æ

	DrawBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount);
}

//…—¬•`‰æ
void WaterGimmick::DrawWaterFlow(int num)
{
	if (isActiveWaterFlow[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, waterFlowBright[num]);
		DrawCircle(waterFlowTransform[num].x, waterFlowTransform[num].y, waterFlowTransform[num].radius, GetColor(255, 255, 255), false);
	}

}

//–A•`‰æ
void WaterGimmick::DrawBubble()
{
	if (isActiveBubble == true)
	{
		DrawCircle(bubbleTransform.x, bubbleTransform.y, bubbleTransform.radius, GetColor(255, 255, 255), false);
	}
}
