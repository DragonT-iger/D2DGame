#include "pch.h"
#include "ArtTestView.h"










void ArtTestView::Awake()
{
	if (!IsActive())
		return;

	//Farmer_35 = Instantiate("Test");
	//Mole_35 = Instantiate("Test");
	Tree_35 = Instantiate("Test");
	Bush_35 = Instantiate("Test");
	EggPlant_35 = Instantiate("Test");
	Photato_35 = Instantiate("Test");
	Pumpkin_35 = Instantiate("Test");

	//Farmer_50 = Instantiate("Test");
	//Mole_50 = Instantiate("Test");
	Tree_50 = Instantiate("Test");
	Bush_50 = Instantiate("Test");
	EggPlant_50 = Instantiate("Test");
	Photato_50 = Instantiate("Test");
	Pumpkin_50 = Instantiate("Test");

	//Farmer_100 = Instantiate("Test");
	//Mole_100 = Instantiate("Test");
	Tree_100 = Instantiate("Test");
	Bush_100 = Instantiate("Test");
	EggPlant_100 = Instantiate("Test");
	Photato_100 = Instantiate("Test");
	Pumpkin_100 = Instantiate("Test");

	//Farmer_150 = Instantiate("Test");
	//Mole_150 = Instantiate("Test");
	Tree_150 = Instantiate("Test");
	Bush_150 = Instantiate("Test");
	EggPlant_150 = Instantiate("Test");
	Photato_150 = Instantiate("Test");
	Pumpkin_150 = Instantiate("Test");

	//Farmer_200 = Instantiate("Test");
	//Mole_200 = Instantiate("Test");
	Tree_200 = Instantiate("Test");
	Bush_200 = Instantiate("Test");
	EggPlant_200 = Instantiate("Test");
	Photato_200 = Instantiate("Test");
	Pumpkin_200 = Instantiate("Test");

	//Farmer_35   ->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("farmer_final.png"));
	//Mole_35->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("mole_final.png"));
	Tree_35->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("tree_re_1.png"));
	Bush_35->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("bush_1.png"));
	EggPlant_35->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	Photato_35->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("potatoL.png"));
	Pumpkin_35->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("pumpkinL.png"));
	//Farmer_50   ->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("farmer_final.png"));
	//Mole_50->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("mole_final.png"));
	Tree_50->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("tree_re_1.png"));
	Bush_50->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("bush_1.png"));
	EggPlant_50->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	Photato_50->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("potatoL.png"));
	Pumpkin_50->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("pumpkinL.png"));
	//Farmer_100  ->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("farmer_final.png"));
	//Mole_100->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("mole_final.png"));
	Tree_100->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("tree_re_1.png"));
	Bush_100->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("bush_1.png"));
	EggPlant_100->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	Photato_100->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("potatoL.png"));
	Pumpkin_100->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("pumpkinL.png"));
	//Farmer_150  ->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("farmer_final.png"));
	//Mole_150->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("mole_final.png"));
	Tree_150->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("tree_re_1.png"));
	Bush_150->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("bush_1.png"));
	EggPlant_150->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	Photato_150->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("potatoL.png"));
	Pumpkin_150->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("pumpkinL.png"));
	//Farmer_200  ->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("farmer_final.png"));
	//Mole_200->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("mole_final.png"));
	Tree_200->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("tree_re_1.png"));
	Bush_200->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("bush_1.png"));
	EggPlant_200->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	Photato_200->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("potatoL.png"));
	Pumpkin_200->AddComponent<SpriteRenderer>()->SetBitmap(ResourceManager::Instance().LoadTexture("pumpkinL.png"));

	//Farmer_35				->GetComponent<Transform>()->SetPosition({ 0,0});
	//Mole_35					->GetComponent<Transform>()->SetPosition({ 0,0});

	int i = 50;

	int j = 200;

	Tree_35					->GetComponent<Transform>()->SetPosition({ 200,0});
	Bush_35					->GetComponent<Transform>()->SetPosition({ 400,0});
	EggPlant_35				->GetComponent<Transform>()->SetPosition({ 600,0});
	Photato_35				->GetComponent<Transform>()->SetPosition({ 800,0});
	Pumpkin_35				->GetComponent<Transform>()->SetPosition({ 1000,0});
	//Farmer_50				->GetComponent<Transform>()->SetPosition({ 0,250});
	//Mole_50					->GetComponent<Transform>()->SetPosition({ 0,250});
	Tree_50					->GetComponent<Transform>()->SetPosition({ 200,250});
	Bush_50					->GetComponent<Transform>()->SetPosition({ 400,250});
	EggPlant_50				->GetComponent<Transform>()->SetPosition({ 600,250});
	Photato_50				->GetComponent<Transform>()->SetPosition({ 800,250});
	Pumpkin_50				->GetComponent<Transform>()->SetPosition({ 1000,250});
	//Farmer_100				->GetComponent<Transform>()->SetPosition({ 0,600});
	//Mole_100				->GetComponent<Transform>()->SetPosition({ 0,600});
	Tree_100				->GetComponent<Transform>()->SetPosition({ 0,650});
	Bush_100				->GetComponent<Transform>()->SetPosition({ 0,650});
	EggPlant_100			->GetComponent<Transform>()->SetPosition({ 0,650});
	Photato_100				->GetComponent<Transform>()->SetPosition({ 0,650});
	Pumpkin_100				->GetComponent<Transform>()->SetPosition({ 0,650});
	//Farmer_150				->GetComponent<Transform>()->SetPosition({ 0,1500});
	//Mole_150				->GetComponent<Transform>()->SetPosition({ 0,1500});
	Tree_150				->GetComponent<Transform>()->SetPosition({ 0,1300});
	Bush_150				->GetComponent<Transform>()->SetPosition({ 0,1300});
	EggPlant_150			->GetComponent<Transform>()->SetPosition({ 0,1300});
	Photato_150				->GetComponent<Transform>()->SetPosition({ 0,1300});
	Pumpkin_150				->GetComponent<Transform>()->SetPosition({ 0,1300});
	//Farmer_200				->GetComponent<Transform>()->SetPosition({ 0,2200});
	//	Mole_200			->GetComponent<Transform>()->SetPosition({ 0,2200});
	Tree_200				->GetComponent<Transform>()->SetPosition({ 0,2200});
	Bush_200				->GetComponent<Transform>()->SetPosition({ 0,2200});
	EggPlant_200			->GetComponent<Transform>()->SetPosition({ 0,2200});
	Photato_200				->GetComponent<Transform>()->SetPosition({ 0,2200});
	Pumpkin_200				->GetComponent<Transform>()->SetPosition({ 0,2200});

	//Farmer_35				->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	//Mole_35					->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	Tree_35					->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	Bush_35					->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	EggPlant_35				->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	Photato_35				->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	Pumpkin_35				->GetComponent<Transform>()->SetScale(Vector2{0.35f,0.35f}                );
	//Farmer_50				->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}                );
	//Mole_50					->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}                );
	Tree_50					->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}                );
	Bush_50					->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}                );
	EggPlant_50				->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}                );
	Photato_50				->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}                );
	Pumpkin_50				->GetComponent<Transform>()->SetScale(Vector2{0.5f,0.5f}             );
	//Farmer_150				->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	//Mole_150				->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	Tree_150				->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	Bush_150				->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	EggPlant_150			->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	Photato_150				->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	Pumpkin_150				->GetComponent<Transform>()->SetScale(Vector2{1.5f,1.5f}                                 );
	//Farmer_200				->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );
	//	Mole_200			->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );
	Tree_200				->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );
	Bush_200				->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );
	EggPlant_200			->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );
	Photato_200				->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );
	Pumpkin_200				->GetComponent<Transform>()->SetScale(Vector2{2,2}                                 );

	Scene::Awake();
}
