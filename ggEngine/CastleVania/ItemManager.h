#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class CVAdd;
class ggEngine::Group;
class CVPreload;
class ItemManager{
public:
	ItemManager(CVGame *cvGame);
	~ItemManager();

	void PreloadAllItem();
	void AddHealthPotion(double x, double y, Group *group);
private:
	CVAdd* cvAdd = nullptr;
	CVPreload *cvPreload = nullptr;
	CVGame *cvGame = nullptr;

	Sprite *heartMini;
	Sprite *heartLarger;
	Sprite *axe;
	Sprite *boomerang;
	Sprite *candle;
	Sprite *crown;
	Sprite *dagger;
	Sprite *cross;
	Sprite *holyWater;
	Sprite *whipUpgrade;
	Sprite *invinPotion;
	Sprite *moneyBag100;
	Sprite *moneyBag400;
	Sprite *moneyBag700;
	Sprite *moneyBag1000;
	Sprite *potRoast;
	Sprite *stopWatch;
	Sprite *stuff;
};