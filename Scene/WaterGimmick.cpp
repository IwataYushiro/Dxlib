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
	//•‚—V…—¬‰Šú‰»
	InitFloating();
}

//…—¬‰Šú‰»
void WaterGimmick::InitWaterflow() {

	//”ÍˆÍ
	this->waterFlowWidth = WIN_WIDTH;						//‰¡•
	this->waterFlowHeight = 10.0f;						//c•
	//…—¬‰Šú‰»
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		this->waterFlowTransform[i].x = waterFlowWidth;		//XÀ•W
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
//•‚—V…—¬‰Šú‰»
void WaterGimmick::InitFloating()
{
	this->floatingWidth = WIN_WIDTH;						//‰¡•
	this->floatingHeight = WIN_HEIGHT;						//c•

	for (int i = 0; i < FLOATING_MAX; i++)
	{
		this->floatingTransform[i].x = floatingWidth - floor_->getSonicFloorpos();	//À•W
		this->floatingTransform[i].y = floatingHeight;
		this->floatingTransform[i].radius = 10.0;//ü‚Å•`‰æ‚·‚é‚©‚çg‚í‚È‚¢
		this->floatingSpeed[i] = 10.0f;			//‘¬“x
		this->floatingBright[i] = 255;		//–¾‚é‚³
		this->isActiveFloating[i] = false;		//¶‚«‚Ä‚é‚©
	}
}


//XV
void WaterGimmick::MarioUpdate(bool isHitBubble)
{
	//…—¬
	UpdateWaterFlow(floor_->getMarioFloorpos());
	//–AXV
	UpdateMarioBubble(isHitBubble);

}
void WaterGimmick::SonicUpdate(bool isHitBubble)
{
	//•‚—V…—¬
	UpdateFloating();
	//–AXV
	UpdateSonicBubble(isHitBubble);

}

//…—¬XV
void WaterGimmick::UpdateWaterFlow(float floorPos)
{
	for (int i = 0; i < WATERFLOW_MAX; i++)
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
	for (int i = 0; i < WATERFLOW_MAX; i++)
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
	if (bubbleCount[mario] <= 0)
	{

		isActiveBubble[mario] = true;
	}
	if (isActiveBubble[mario] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[mario].y -= bubbleSpeed[mario];
		}

		if (bubbleTransform[mario].y <= 0.0f || isHit == true)
		{
			bubbleTransform[mario].x = bubbleWidth[mario];
			bubbleTransform[mario].y = bubbleHeight[mario];
			isActiveBubble[mario] = false;
			bubbleCount[mario] = 60 * 4;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[mario]--;
	}
}

void WaterGimmick::UpdateSonicBubble(bool& isHit)
{
	if (bubbleCount[sonic] <= 0)
	{
		bubbleCount[sonic] = 0;
		isActiveBubble[sonic] = true;
	}
	if (isActiveBubble[sonic] == true)
	{
		if (isHit == false)
		{
			bubbleTransform[sonic].y -= bubbleSpeed[sonic];
		}

		if (bubbleTransform[sonic].y <= 0.0f || isHit == true)
		{
			bubbleTransform[sonic].x = bubbleWidth[sonic];
			bubbleTransform[sonic].y = bubbleHeight[sonic];
			isActiveBubble[sonic] = false;
			bubbleCount[sonic] = 60 * 4;
			isHit = false;
		}
	}
	else
	{

		bubbleCount[sonic]--;
	}
}

// •‚—V…—¬XV
void WaterGimmick::UpdateFloating()
{
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		if (isActiveFloating[i] == false)
		{
			isActiveFloating[i] = true;
			floatingTransform[i].x = floatingWidth - rand() % 300;
			floatingTransform[i].y = floatingHeight;
			if (i % 2 == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		if (isActiveFloating[i] == true)
		{
			floatingBright[i] -= 2;
			floatingTransform[i].y -= floatingSpeed[i];
		}
		if (floatingBright[i] <= 0)
		{
			isActiveFloating[i] = false;
			floatingBright[i] = 255;
		}
	}
}

//ƒŠƒZƒbƒg
void WaterGimmick::Reset()
{
	waterFlowWidth = WIN_WIDTH - 200.0f;
	waterFlowHeight = 10.0f;

	for (int i = 0; i < WATERFLOW_MAX; i++)
	{

		waterFlowTransform[i].x = waterFlowWidth;		//XÀ•W
		waterFlowTransform[i].y = floor_->getMarioFloorpos() - waterFlowHeight;
		waterFlowTransform[i].radius = 5.0f;		//…—¬–A‚Ì”¼Œa
		waterFlowSpeed[i] = 5.0f;			//‘¬“x
		waterFlowBright[i] = 255;		//–¾‚é‚³
		isActiveWaterFlow[i] = false;		//¶‚«‚Ä‚é‚©
	}

	for (int i = 0; i < jumpLength; i++)
	{

		//”ÍˆÍ
		bubbleWidth[i] = 200.0f;														//‰¡•
		bubbleHeight[i] = WIN_HEIGHT;						//c•
		//–A‰Šú‰»

		bubbleTransform[i].x = bubbleWidth[i];		//XÀ•W
		bubbleTransform[i].y = bubbleHeight[i];			//YÀ•W
		bubbleTransform[i].radius = 32.0f;		//…—¬–A‚Ì”¼Œa
		bubbleSpeed[i] = 5.0f;			//‘¬“x
		isActiveBubble[i] = false;		//¶‚«‚Ä‚é‚©

		//–A‚Ì“–‚½‚è”»’è—p
		bubbleHit[i].x = 0.0f;
		bubbleHit[i].y = 0.0f;
		bubbleHit[i].z = 0.0f;

		//–A‚ªo‚éƒ^ƒCƒ~ƒ“ƒO
		bubbleCount[i] = 60 * 4;
	}

	//•‚—V…—¬
	this->floatingWidth = WIN_WIDTH;						//‰¡•
	this->floatingHeight = WIN_HEIGHT;						//c•

	for (int i = 0; i < FLOATING_MAX; i++)
	{
		this->floatingTransform[i].x = floatingWidth - floor_->getSonicFloorpos();	//À•W
		this->floatingTransform[i].y = floatingHeight;
		this->floatingTransform[i].radius = 10.0f;//ü‚Ì’·‚³
		this->floatingSpeed[i] = 10.0f;			//‘¬“x
		this->floatingBright[i] = 255;		//–¾‚é‚³
		this->isActiveFloating[i] = false;		//¶‚«‚Ä‚é‚©
	}
}


//•`‰æ
void WaterGimmick::DrawMario()
{
	//…—¬•`‰æ
	for (int i = 0; i < WATERFLOW_MAX; i++)
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
	//•‚—V…—¬•`‰æ
	for (int i = 0; i < FLOATING_MAX; i++)
	{
		DrawFloating(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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

//•‚—V…—¬•`‰æ
void WaterGimmick::DrawFloating(int num)
{
	if (isActiveFloating[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, floatingBright[num]);
		//DrawLine(floatingTransform[num].x, floatingTransform[num].y, floatingTransform[num].x, floatingTransform[num].y + floatingTransform[num].radius, GetColor(255, 255, 255), 2);
		DrawCircle(floatingTransform[num].x, floatingTransform[num].y, floatingTransform[num].radius, GetColor(255, 255, 255), false);
	}
}
//“–‚½‚è”»’è
//“–‚½‚è”»’è—pŠÖ”
void WaterGimmick::IsHitBubbleMario(Transform& transform, bool& isHit)
{
	bubbleHit[mario].x = transform.x - bubbleTransform[mario].x;
	bubbleHit[mario].y = transform.y - bubbleTransform[mario].y;
	bubbleHit[mario].z = bubbleHit[mario].x * bubbleHit[mario].x + bubbleHit[mario].y * bubbleHit[mario].y;
	//–A‚ªo‚Ä‚é‚Æ‚«
	if (isActiveBubble[mario] == true && isHit == false)
	{
		//“–‚½‚Á‚Ä‚é‚©
		if (bubbleHit[mario].z <= (bubbleTransform[mario].radius + transform.radius) *
			(bubbleTransform[mario].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[mario] = false;
	}
}

void WaterGimmick::IsHitBubbleSonic(Transform& transform, bool& isHit)
{
	bubbleHit[sonic].x = transform.x - bubbleTransform[sonic].x;
	bubbleHit[sonic].y = transform.y - bubbleTransform[sonic].y;
	bubbleHit[sonic].z = bubbleHit[sonic].x * bubbleHit[sonic].x + bubbleHit[sonic].y * bubbleHit[sonic].y;
	//–A‚ªo‚Ä‚é‚Æ‚«
	if (isActiveBubble[sonic] == true && isHit == false)
	{
		//“–‚½‚Á‚Ä‚é‚©
		if (bubbleHit[sonic].z <= (bubbleTransform[sonic].radius + transform.radius) *
			(bubbleTransform[sonic].radius + transform.radius))
		{
			isHit = true;
		}

	}
	if (isHit == true)
	{
		isActiveBubble[sonic] = false;

	}
}

