#include "TestStateCastleVania.h"

TestStateCastleVania::TestStateCastleVania(CVGame *game) :CVState(game)
{
}
TestStateCastleVania::~TestStateCastleVania()
{
}
void TestStateCastleVania::Init() {

}
void TestStateCastleVania::Preload() {
	this->cvPreload->FontGame();
	this->cvPreload->UIInfoPanel();
	this->cvPreload->CharSimon();
}
void TestStateCastleVania::Create()
{
	this->cvAdd->UIInfoPanel();
	Group* group = this->cvAdd->Group();
	this->simon = this->cvAdd->CharSimon(400, 400, group);



}
void TestStateCastleVania::Update()
{

}
void TestStateCastleVania::PreRender()
{
}
void TestStateCastleVania::Render()
{

}
void TestStateCastleVania::Pause()
{
}
void TestStateCastleVania::Resume()
{
}
void TestStateCastleVania::ShutDown()
{

}

