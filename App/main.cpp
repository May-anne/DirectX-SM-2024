#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

// Link com a biblioteca DirectX
#pragma comment (lib, "d3d11.lib")

// Variáveis globais
IDXGISwapChain *swapchain;             // O ponteiro da cadeia de troca (swap chain)
ID3D11Device *dev;                     // O ponteiro para o dispositivo (device)
ID3D11DeviceContext *devcon;           // O ponteiro para o contexto do dispositivo (device context)
ID3D11RenderTargetView *backbuffer;    // O ponteiro para a visão do buffer de volta (backbuffer view)

// Prototipos das funções
void InitD3D(HWND hWnd);    // Configura o Direct3D
void RenderFrame(void);     // Renderiza um frame
void CleanD3D(void);        // Limpa o Direct3D

// A função WinMain é o ponto de entrada do Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
                          "WindowClass",
                          "Nossa Primeira Janela",
                          WS_OVERLAPPEDWINDOW,
                          300, 300,
                          800, 600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, nCmdShow);

    // Inicializa o Direct3D
    InitD3D(hWnd);

    // Loop principal da mensagem
    MSG msg = {0};
    while (TRUE)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            break;

        // Renderiza um frame
        RenderFrame();
    }

    // Limpa o Direct3D
    CleanD3D();

    return msg.wParam;
}

// Processa mensagens da janela
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Inicializa o Direct3D
void InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;                                    // um back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // formato 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // como o buffer vai ser usado
    scd.OutputWindow = hWnd;                                // janela de saída
    scd.SampleDesc.Count = 4;                               // nível de multisampling
    scd.Windowed = TRUE;                                    // janela modo ou fullscreen

    // Cria um dispositivo, contexto de dispositivo e cadeia de swap
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &swapchain,
                                  &dev,
                                  NULL,
                                  &devcon);

    // Obter o endereço do back buffer
    ID3D11Texture2D *pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // Usa o back buffer para criar uma visão de renderização
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // Define a visão de renderização como o alvo
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);

    // Configura o viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = 800;
    viewport.Height = 600;

    devcon->RSSetViewports(1, &viewport);
}

// Renderiza um frame
void RenderFrame(void)
{
    // Limpa o buffer para uma cor azul
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    // Aqui, desenhamos a cena

    // Apresenta o back buffer para a tela
    swapchain->Present(0, 0);
}

// Limpa o Direct3D
void CleanD3D(void)
{
    swapchain->Release();
    backbuffer->Release();
    dev->Release();
    devcon->Release();
}
