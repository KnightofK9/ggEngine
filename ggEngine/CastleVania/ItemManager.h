#include <ggEngine.h>
#include "CVAdd.h"
#include "Heart.h"
using namespace ggEngine;
class CVGame;
class ggEngine::Group;
class CVPreload;
class ItemManager : protected CVAdd{
public:
	ItemManager(CVGame *cvGame);
	~ItemManager();

	void PreloadAllItem();
	Heart* AddHeart(double x, double y, ggEngine::Group* group);
private:
	CVPreload *cvPreload = nullptr;
	CVGame *cvGame = nullptr;
};