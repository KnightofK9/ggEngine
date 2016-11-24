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
};