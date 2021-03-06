#include "HealthBar.h"
#include "CVGame.h"
HealthBar::HealthBar(CVGame *cvGame) : ScreenGroup(cvGame)
{
	this->SetMask(true);
}

HealthBar::~HealthBar()
{
}

void HealthBar::SetHealth(int currentHealth)
{
	if (currentHealth > maxHealth) currentHealth = maxHealth;
	this->currentHealth = currentHealth;
	SetWidth((originWidth / this->maxHealth)*this->currentHealth);
}

void HealthBar::SetEmptyHealthBar(Sprite * emptyHealthBar)
{
	this->emptyHealthBar = emptyHealthBar;
	this->SetWidth(emptyHealthBar->GetImage()->GetWidth());
	this->SetHeight(emptyHealthBar->GetImage()->GetHeight());
}

void HealthBar::SetHealthBar(Sprite * healthBar, int maxHealth)
{
	this->healthBar = healthBar;
	this->maxHealth = maxHealth;
	this->originWidth = healthBar->GetWidth();
}

void HealthBar::Draw()
{
	this->UpdateWorldPosition();
	if ((this)->IsVisible()) {
		//this->drawManager->DrawList(this->GetDrawList(), this->isUsedMask);
		if (this->emptyHealthBar != nullptr) {
			this->emptyHealthBar->UpdateWorldPosition();
			this->emptyHealthBar->Draw();
		}
		if (this->healthBar != nullptr) {
			this->healthBar->UpdateWorldPosition();
			this->healthBar->DrawRect();
		}
	}

	//ScreenGroup::Draw();
	/*this->UpdateWorldPosition();
	if (!(this)->IsVisible()) return;
	if (this->emptyHealthBar != nullptr) this->emptyHealthBar->Draw();
	if (this->healthBar != nullptr) this->healthBar->DrawRect();*/
}



