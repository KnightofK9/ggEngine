#include <ggEngine.h>
#include "CVAdd.h"
#include "Heart.h"
#include "AxeItem.h"
#include "MoneyBag100.h"
#include "MoneyBag400.h"
#include "MoneyBag700.h"
#include "MoneyBag1000.h"
#include "PotRoast.h"
#include "BoomerangItem.h"
#include "InvinPotion.h"
#include "Cross.h"
#include "Crown.h"
#include "HolyWaterItem.h"
#include "StopWatch.h"
#include "DaggerItem.h"
#include "HeartLarger.h"
#include "WhipUpgradeItem.h"
#include "Stuff.h"
#include "DoubleShot.h"
#include "TripleShot.h"
#include "Candle.h"
#include "ManagerBase.h"

using namespace ggEngine;
class ggEngine::Group;
class CVPreload;
class CVAdd;
class ItemManager : public ManagerBase{
public:
	ItemManager(CVGame *cvGame);
	virtual ~ItemManager();

	void PreloadAllItem();
	Candle* AddFireCandle(double x, double y, ggEngine::Group* group);
	Heart* AddHeart(double x, double y, ggEngine::Group* group);
	AxeItem* AddAxe(double x, double y, ggEngine::Group* group);
	MoneyBag100* AddMoneyBag100(double x, double y, ggEngine::Group * group);
	MoneyBag400* AddMoneyBag400(double x, double y, ggEngine::Group * group);
	MoneyBag700* AddMoneyBag700(double x, double y, ggEngine::Group * group);
	MoneyBag1000* AddMoneyBag1000(double x, double y, ggEngine::Group * group);
	HolyWaterItem* AddHolyWater(double x, double y, ggEngine::Group * group);
	DaggerItem* AddDagger(double x, double y, ggEngine::Group * group);
	Cross* AddCross(double x, double y, ggEngine::Group * group);
	Crown* AddCrown(double x, double y, ggEngine::Group * group);
	StopWatch* AddStopWatch(double x, double y, ggEngine::Group * group);
	PotRoast* AddPotRoast(double x, double y, ggEngine::Group * group);
	InvinPotion* AddInvinPotion(double x, double y, ggEngine::Group * group);
	HeartLarger* AddHeartLarger(double x, double y, ggEngine::Group * group);
	WhipUpgradeItem* AddWhipUpgrade(double x, double y, ggEngine::Group * group);
	Stuff* AddStuff(double x, double y, ggEngine::Group * group);
	BoomerangItem* AddBoomerang(double x, double y, ggEngine::Group * group);
	DoubleShot* AddDoubleShot(double x, double y, ggEngine::Group * group);
	TripleShot* AddTripleShot(double x, double y, ggEngine::Group * group);


private:
	CVPreload *cvPreload = nullptr;
	CVAdd *cvAdd = nullptr;
};