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
		this->waterFlowTransform[i].y = floor_->getFloorpos() - waterFlowHeight;			//YÀ•W
		this->waterFlowTransform[i].radius = 5;		//…—¬–A‚Ì”¼Œa
		this->waterFlowSpeed[i] = 5;			//‘¬“x
		this->waterFlowBright[i] = 255;		//–¾‚é‚³
		this->waterFlowIsActive[i] = false;		//¶‚«‚Ä‚é‚©
	}
	//–A‚Ì“–‚½‚è”»’è—p
	this->waterFlowHit.x = 0;
	this->waterFlowHit.y = 0;
	this->waterFlowHit.z = 0;
}

//–A‰Šú‰»
void WaterGimmick::InitBubble()
{
	//”ÍˆÍ
	this->bubbleWidth = 200.0f;														//‰¡•
	this->bubbleHeight = floor_->getFloorpos();						//c•
	//–A‰Šú‰»

	this->bubbleTransform.x = waterFlowWidth;		//XÀ•W
	this->bubbleTransform.y = waterFlowHeight;			//YÀ•W
	this->bubbleTransform.radius = 32;		//…—¬–A‚Ì”¼Œa
	this->bubbleSpeed = 5;			//‘¬“x
	this->bubbleIsActive = false;		//¶‚«‚Ä‚é‚©

	//…—¬‚Ì“–‚½‚è”»’è—p
	this->bubbleHit.x = 0;
	this->bubbleHit.y = 0;
	this->bubbleHit.z = 0;

	//–A‚ªo‚éƒ^ƒCƒ~ƒ“ƒO
	this->bubbleCount = 60.0f * 4.0f;
}





//XV
void WaterGimmick::Update()
{
	//…—¬
	UpdateWaterFlow();
	//–AXV
	UpdateBubble();
	
}

//…—¬XV
void WaterGimmick::UpdateWaterFlow()
{
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (waterFlowIsActive[i] == false)
		{
			waterFlowIsActive[i] = true;
			waterFlowTransform[i].x = WIN_WIDTH;
			waterFlowTransform[i].y = floor_->getFloorpos() - waterFlowHeight;
			if (i % 2 == 0)
			{
				break;
			}
		}
	}
	for (int i = 0; i < EMITTER_MAX; i++)
	{

		if (waterFlowIsActive[i] == true)
		{
			waterFlowBright[i] -= 2;
			waterFlowTransform[i].x -= waterFlowSpeed[i];
			waterFlowTransform[i].y -= rand() % 5 - 2;
		}
		if (waterFlowBright[i] <= 0)
		{
			waterFlowIsActive[i] = false;
			waterFlowBright[i] = 255;
		}
	}
}

//–AXV
void WaterGimmick::UpdateBubble()
{
	if (bubbleIsActive == false)
	{
		bubbleIsActive = true;
		bubbleTransform.x = bubbleWidth;
		bubbleTransform.y = bubbleHeight;
	}
	
	if (bubbleIsActive == true)
	{
		bubbleTransform.y -= bubbleSpeed;

	}
	if (bubbleTransform.y < 0.0f && bubbleCount < 0.0f)
	{
		bubbleTransform.x = bubbleWidth;
		bubbleTransform.y = bubbleHeight;
		bubbleIsActive = false;
		bubbleCount = rand() % 150 + 50;
	}
	bubbleCount--;

}



//•`‰æ
void WaterGimmick::Draw()
{
	//…—¬•`‰æ
	for (int i = 0; i < EMITTER_MAX; i++)
	{
		DrawWaterFlow(i);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//–A•`‰æ
	DrawBubble();
	DrawFormatString(0, 60, GetColor(255, 255, 255), "bubble::%f", bubbleCount);
}

//…—¬•`‰æ
void WaterGimmick::DrawWaterFlow(int num)
{
	if (waterFlowIsActive[num] == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, waterFlowBright[num]);
		DrawCircle(waterFlowTransform[num].x, waterFlowTransform[num].y, waterFlowTransform[num].radius, GetColor(255, 255, 255), false);
	}

}

//–A•`‰æ
void WaterGimmick::DrawBubble()
{
	if (bubbleIsActive == true)
	{
		DrawCircle(bubbleTransform.x, bubbleTransform.y, bubbleTransform.radius, GetColor(255, 255, 255), false);
	}
	
}
