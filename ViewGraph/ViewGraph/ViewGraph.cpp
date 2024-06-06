#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

class SpriteDemo : public Game
{
private:
    Sprite* backg = nullptr;            // sprite do fundo de tela
    Sprite* grafico1 = nullptr;            // sprite do grafico 1 
    Sprite* grafico2 = nullptr;            // sprite do grafico 2

    float x1 = 0, y1 = 0;                    // posição x,y do shank
    float x2 = 0, y2 = 0;                    // posição x,y do shank

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------

void SpriteDemo::Init()
{
    backg = new Sprite("Resources/Background.jpg");
    grafico1 = new Sprite("Resources/ConstTropicana_1.png");
    grafico2 = new Sprite("Resources/ConstCapiba_1.png");


    x1 = 80.0f;
    y1 = 90.0f;
    x2 = 90.0f;
    y2 = 80.0f;
}

// ------------------------------------------------------------------------------

void SpriteDemo::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // desloca graficos
    if (window->KeyDown(VK_LEFT))
        x1 -= 50.0f * gameTime;
    if (window->KeyDown(VK_RIGHT))
        x1 += 50.0f * gameTime;
    if (window->KeyDown(VK_UP))
        y1 -= 50.0f * gameTime;
    if (window->KeyDown(VK_DOWN))
        y1 += 50.0f * gameTime;

    if (window->KeyDown(VK_NUMPAD4))
        x2 -= 50.0f * gameTime;
    if (window->KeyDown(VK_NUMPAD6))
        x2 += 50.0f * gameTime;
    if (window->KeyDown(VK_NUMPAD8))
        y2 -= 50.0f * gameTime;
    if (window->KeyDown(VK_NUMPAD5))
        y2 += 50.0f * gameTime;
}

// ------------------------------------------------------------------------------

void SpriteDemo::Draw()
{
    backg->Draw(0.0f, 0.0f, Layer::BACK);
    grafico1->Draw(x1, y1);
    grafico2->Draw(x2, y2);

}

// ------------------------------------------------------------------------------

void SpriteDemo::Finalize()
{
    // remove sprites da memória
    delete backg;
    delete grafico1;
    delete grafico2;

}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor de jogo
    Engine* engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Visualizando dados");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new SpriteDemo());

    // destrói o motor e o jogo
    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

