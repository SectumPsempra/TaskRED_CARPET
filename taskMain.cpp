#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

// Variáveis de controle
int error_scale = 15,
    quality = 75;

// Matrizes para as imagens
cv::Mat img_one,
        img_two;

void processImage(int, void*, IMAGE)
{
    // Configuração dos params e compressão JPEG
    std::vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(quality);
    cv::imwrite(IMAGE, img_one, params);

    // Leitura da imagem temporária do disco
    img_two = cv::imread(IMAGE);

    if (img_two.empty())
    {
        std::cout << "> Error image has no pixels" << std::endl;
        exit(EXIT_FAILURE);
    }

    cv::Mat img_s = cv::Mat::zeros(img_one.size(), CV_8UC3);

    // Percorre as matrizes comparando os valores
    for (int line = 0; line < img_one.rows; ++line)
    {
          const uchar*  ptr_e = img_one.ptr<uchar>(line);
          const uchar*  ptr_c = img_two.ptr<uchar>(line);
                uchar*  ptr_s = img_s.ptr<uchar>(line);

        for (int column = 0; column < img_one.cols; column++)
        {
            // Cálculo da diferença absoluta em cada canal de cor, multiplicado pela error_scale
            ptr_s[0] = abs(ptr_e[0] - ptr_c[0]) * error_scale;
            ptr_s[1] = abs(ptr_e[1] - ptr_c[1]) * error_scale;
            ptr_s[2] = abs(ptr_e[2] - ptr_c[2]) * error_scale;

            ptr_e += 3;
            ptr_c += 3;
            ptr_s += 3;
        }
    }

    // Exibe imagem processada
    cv::imshow("Error Level Analysis", img_s);

}

int main (int argc, char* argv[])
{
    // Verifica se o número de parâmetros necessário foi informado
    if (argc < 2)
    {
        std::cout << "> Image not found" << std::endl;
        return EXIT_FAILURE;
    }

    // Lê a imagem passada por parâmetro
    img_one = cv::imread(argv[1]);

    // Verifica se a imagem foi carregada corretamente
    if (img_one.empty())
    {
        std::cout << "> Empty image" << std::endl;
        return EXIT_FAILURE;
    }

    // Configuração da janela e dos componentes
    cv::namedWindow("ELA", CV_WINDOW_AUTOSIZE);
    cv::imshow("ELA", img_one);
    cv::createTrackbar("error_scale", "ELA", &error_scale, 100, processImage);
    cv::createTrackbar("quality", "ELA", &quality, 100, processImage);

    // Aguarda até que a tela 'q' seja pressionada para encerrar o programa
    while (char(cv::waitKey(0)) != 'q') {};

    return EXIT_SUCCESS;
}