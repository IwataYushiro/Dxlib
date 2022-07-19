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
	for (int i = 0; i < jumpLength; i++)
	{
		//”ÍˆÍ
		this->bubbleWidth[i] = 200.0f;														//‰¡•
		this->bubbleHeight[i] = WIN_HEIGHT;						//c•
		//–A‰Šú‰»

		this->bubbleTransform[i].x = bubbleWidth[i];		//XÀ•W
		this->bubbleTransform[i].y = bubbleHeight[i];			//YÀ•W
		this->bubbleTransform[i].radius = 32.0f;		//…—¬–A‚Ì”¼Œa
		this->bubbleSpeed[i] = 5.0f;			//‘¬“x
		this->isActiveBubble[i] = false;		//¶‚«‚Ä‚é‚©

		//–A‚Ì“–‚½‚è”»’è—p
		this->bubbleHit[i].x = 0.0f;
		this->bubbleHit[i].y = 0.0f;
		this->bubbleHit[i].z = 0.0f;

		//–A‚ªo‚éƒ^ƒCƒ~ƒ“ƒO
		this->bubbleCount[i] = 60 * 4;
	}

}

//XV
void WaterGimmick::MarioUpdate(bool& isHitBubble)
{
	//…—¬
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//–AXV
	UpdateMarioBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool& isHitBubble)
{
	//–AXV
	UpdateSonicBubble(isHitBubble);

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
void WaterGimmick::UpdateMarioBubble(bool& isHit)
{
		if (bubbleCount[0] <= 0)
		{
			bubbleCount[0] = 0;
			isActiveBubble[0] = true;
		}
		if (isActiveBubble[0] == true)
		{
			if (isHit == false)
			{
				bubbleTransform[0].y -= bubbleSpeed[0];
			}

			if (bubbleTransform[0].y <= 0.0f || isHit == true)
			{
				bubbleTransform[0].x = bubbleWidth[0];
				bubbleTransform[0].y = bubbleHeight[0];
				isActiveBubble[0] = false;
				isHit = false;
			}
		}
		else
		{

			bubbleCount[0]--;
		}
}

void WaterGimmick::UpdateSonicBubble(bool& isHit)
{
	if (bubbleCount[1] <= 0)
	{
		bubbleCount[1] = 0;
		isActiveBubble[1] = true;
	}
	if (isActiveBubble[1] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[1].y -= bubbleSpeed[1];
		}

		if (bubbleTransform[1].y <= 0.0f || isHit == true)
		{
			bubbleTransform[1].x = bubbleWidth[1];
			bubbleTransform[1].y = bubbleHeight[1];
			isActiveBubble[1] = false;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[1]--;
	}
}
//“–‚½‚è”»’è
//“–‚½‚è”»’è—pŠÖ”
void WaterGimmick::IsHitBubbleMario(Transform& transform, bool& isHit)
{
		bubbleHit[0].x = transform.x - bubbleTransform[0].x;
		bubbleHit[0].y = transform.y - bubbleTransform[0].y;
		bubbleHit[0].z = bubbleHit[0].x * bubbleHit[0].x + bubbleHit[0].y * bubbleHit[0].y;
		//–A‚ªo‚Ä‚é‚Æ‚«
		if (isActiveBubble[0] == true && isHit == false)
		{
			//“–‚½‚Á‚Ä‚é‚©
			if (bubbleHit[0].z <= (bubbleTransform[0].radius + transform.radius) *
				(bubbleTransform[0].radius + transform.radius))
			{
				isHit = true;
			}

		}
		if (isHit == true)
		{
			isActiveBubble[0] = false;

		}

		DrawFormatString(0, 90, GetColor(255, 255, 255), "bubble::%f,%f,%f", bubbleHit[0].x, bubbleHit[0].y, bubbleHit[0].z);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "pt,bt::%f,%f", transform.y, bubbleTransform[0].y);
}

void WaterGimmick::IsHitBubbleSonic(Transform& transform, bool& isHit)
{
	bubbleHit[1].x = transform.x - bubbleTransform[1].x;
	bubbleHit[1].y = transform.y - bubbleTransform[1].y;
	bubbleHit[1].z = bubbleHit[1].x * bubbleHit[1].x + bubbleHit[1].y * bubbleHit[1].y;
	//–A‚ªo‚Ä‚é‚Æ‚«
	if (isActiveBubble[1] == true && isHit == false)
	{
		//“–‚½‚Á‚Ä‚é‚©
		if (bubbleHit[1].z <= (bubbleTransform[1].radius + transform.radius) *
			(bubbleTransform[1].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[1] = false;

	}

	DrawFormatString(0, 90, GetColor(255, 255, 255), "bubble::%f,%f,%f", bubbleHit[1].x, bubbleHit[1].y, bubbleHit[1].z);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "pt,bt::%f,%f", transform.y, bubbleTransform[1].y);
}

//•`‰æ
void WaterGimmick::DrawMario()
{
	//…—¬•`‰æ
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//–A•`‰æ

	DrawMarioBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount[mario]);
}
void WaterGimmick::DrawSonic()
{
	//–A•`‰æ
	DrawSonicBubble();

	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%d", bubbleCount[sonic]);
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
void WaterGimmick::DrawMarioBubble()
{
	if (isActiveBubble[mario] == true)
	{
		DrawCircle(bubbleTransform[mario].x, bubbleTransform[mario].y, bubbleTransform[mario].radius, GetColor(255, 255, 255), false);
	}
}

void WaterGimmick::DrawSonicBubble()
{
	if (isActiveBubble[sonic] == true)
	{
		DrawCircle(bubbleTransform[sonic].x, bubbleTransform[sonic].y, bubbleTransform[sonic].radius, GetColor(255, 255, 255), false);
	}
}

