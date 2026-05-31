#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

int roundoff(float e);
bool check(int a, int b, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            int x = roundoff(average);

            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtRed = x;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue;

            int x = roundoff(sepiaRed);
            int y = roundoff(sepiaBlue);
            int z = roundoff(sepiaGreen);

            if (x > 255)
            {
                x = 255;
            }
            if (y > 255)
            {
                y = 255;
            }
            if (z > 255)
            {
                z = 255;
            }

            image[i][j].rgbtBlue = y;
            image[i][j].rgbtGreen = z;
            image[i][j].rgbtRed = x;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            if (width % 2 != 0)
            {
                if (j != (width / 2))
                {
                    int a;
                    a = image[i][j].rgbtRed;
                    image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                    image[i][width - j - 1].rgbtRed = a;

                    a = image[i][j].rgbtBlue;
                    image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                    image[i][width - j - 1].rgbtBlue = a;

                    a = image[i][j].rgbtGreen;
                    image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                    image[i][width - j - 1].rgbtGreen = a;
                }

                if (j == (width / 2))
                {
                    continue;
                }
            }
            else
            {
                int a;
                a = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][width - j - 1].rgbtRed = a;

                a = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtBlue = a;

                a = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][width - j - 1].rgbtGreen = a;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            copy[m][n] = image[m][n];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Corner case 1
            if (i == 0 && j == 0)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;
                for (int k = i; k <= i + 1; k++)
                {
                    for (int l = j; l <= j + 1; l++)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }
            // Corner case 2
            else if (i == 0 && j == width - 1)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i; k <= i + 1; k++)
                {
                    for (int l = j; l >= j - 1; l--)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }
            // Corner case 3
            else if (i == height - 1 && j == 0)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i; k >= i - 1; k--)
                {
                    for (int l = j; l <= j + 1; l++)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }
            // Corner case 4
            else if (i == height - 1 && j == width - 1)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i; k >= i - 1; k--)
                {
                    for (int l = j; l >= j - 1; l--)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }

            // Edge case horizontal 1
            if (i == 0)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }

            // Edge case horizontal 2
            if (i == height - 1)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i; k >= i - 1; k--)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }

            // Edge case vertical 1
            if (j == 0)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j; l <= j + 1; l++)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }

            // Edge case vertical 2
            if (j == width - 1)
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j; l >= j - 1; l--)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }

            // Others
            else
            {
                int sumR = 0;
                int sumG = 0;
                int sumB = 0;
                int cases = 0;

                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        cases += 1;
                        sumR += copy[k][l].rgbtRed;
                        sumG += copy[k][l].rgbtGreen;
                        sumB += copy[k][l].rgbtBlue;
                    }
                }

                int averageR = roundoff((sumR / (float) cases));
                int averageG = roundoff((sumG / (float) cases));
                int averageB = roundoff((sumB / (float) cases));

                image[i][j].rgbtRed = averageR;
                image[i][j].rgbtGreen = averageG;
                image[i][j].rgbtBlue = averageB;

                continue;
            }
        }
    }

    return;

    free(copy);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculating Sobel Operator values
    RGBTRIPLE(*copy)[width] = calloc((height), (width) * sizeof(RGBTRIPLE));
    for (int z = 0; z < height; z++)
    {
        for (int t = 0; t < width; t++)
        {
            copy[z][t] = image[z][t];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Gx
            int *R = malloc(9 * sizeof(int));
            int *G = malloc(9 * sizeof(int));
            int *B = malloc(9 * sizeof(int));

            if (check(i, j, height, width))
            {
                R[4] = 0;
                G[4] = 0;
                B[4] = 0;
            }
            else
            {
                R[4] = copy[i][j].rgbtRed * 0;
                G[4] = copy[i][j].rgbtGreen * 0;
                B[4] = copy[i][j].rgbtBlue * 0;
            }

            if (check(i - 1, j, height, width))
            {
                R[1] = 0;
                G[1] = 0;
                B[1] = 0;
            }
            else
            {
                R[1] = copy[i - 1][j].rgbtRed * 0;
                G[1] = copy[i - 1][j].rgbtGreen * 0;
                B[1] = copy[i - 1][j].rgbtBlue * 0;
            }

            if (check(i + 1, j, height, width))
            {
                R[7] = 0;
                G[7] = 0;
                B[7] = 0;
            }
            else
            {
                R[7] = copy[i + 1][j].rgbtRed * 0;
                G[7] = copy[i + 1][j].rgbtGreen * 0;
                B[7] = copy[i + 1][j].rgbtBlue * 0;
            }

            if (check(i + 1, j - 1, height, width))
            {
                R[6] = 0;
                G[6] = 0;
                B[6] = 0;
            }
            else
            {
                R[6] = copy[i + 1][j - 1].rgbtRed * -1;
                G[6] = copy[i + 1][j - 1].rgbtGreen * -1;
                B[6] = copy[i + 1][j - 1].rgbtBlue * -1;
            }

            if (check(i, j - 1, height, width))
            {
                R[3] = 0;
                G[3] = 0;
                B[3] = 0;
            }
            else
            {
                R[3] = copy[i][j - 1].rgbtRed * -2;
                G[3] = copy[i][j - 1].rgbtGreen * -2;
                B[3] = copy[i][j - 1].rgbtBlue * -2;
            }

            if (check(i - 1, j - 1, height, width))
            {
                R[0] = 0;
                G[0] = 0;
                B[0] = 0;
            }
            else
            {
                R[0] = copy[i - 1][j - 1].rgbtRed * -1;
                G[0] = copy[i - 1][j - 1].rgbtGreen * -1;
                B[0] = copy[i - 1][j - 1].rgbtBlue * -1;
            }

            if (check(i + 1, j + 1, height, width))
            {
                R[8] = 0;
                G[8] = 0;
                B[8] = 0;
            }
            else
            {
                R[8] = copy[i + 1][j + 1].rgbtRed * 1;
                G[8] = copy[i + 1][j + 1].rgbtGreen * 1;
                B[8] = copy[i + 1][j + 1].rgbtBlue * 1;
            }

            if (check(i, j + 1, height, width))
            {
                R[5] = 0;
                G[5] = 0;
                B[5] = 0;
            }
            else
            {
                R[5] = copy[i][j + 1].rgbtRed * 2;
                G[5] = copy[i][j + 1].rgbtGreen * 2;
                B[5] = copy[i][j + 1].rgbtBlue * 2;
            }

            if (check(i - 1, j + 1, height, width))
            {
                R[2] = 0;
                G[2] = 0;
                B[2] = 0;
            }
            else
            {
                R[2] = copy[i - 1][j + 1].rgbtRed * 1;
                G[2] = copy[i - 1][j + 1].rgbtGreen * 1;
                B[2] = copy[i - 1][j + 1].rgbtBlue * 1;
            }

            int GxR = 0;
            for (int c = 0; c < 9; c++)
            {
                GxR += R[c];
            }

            int GxG = 0;
            for (int c = 0; c < 9; c++)
            {
                GxG += G[c];
            }

            int GxB = 0;
            for (int c = 0; c < 9; c++)
            {
                GxB += B[c];
            }

            // Gy

            int *r = malloc(9 * sizeof(int));
            int *g = malloc(9 * sizeof(int));
            int *b = malloc(9 * sizeof(int));

            if (check(i, j, height, width))
            {
                r[4] = 0;
                g[4] = 0;
                b[4] = 0;
            }
            else
            {
                r[4] = copy[i][j].rgbtRed * 0;
                g[4] = copy[i][j].rgbtGreen * 0;
                b[4] = copy[i][j].rgbtBlue * 0;
            }

            if (check(i - 1, j, height, width))
            {
                r[1] = 0;
                g[1] = 0;
                b[1] = 0;
            }
            else
            {
                r[1] = copy[i - 1][j].rgbtRed * -2;
                g[1] = copy[i - 1][j].rgbtGreen * -2;
                b[1] = copy[i - 1][j].rgbtBlue * -2;
            }

            if (check(i + 1, j, height, width))
            {
                r[7] = 0;
                g[7] = 0;
                b[7] = 0;
            }
            else
            {
                r[7] = copy[i + 1][j].rgbtRed * 2;
                g[7] = copy[i + 1][j].rgbtGreen * 2;
                b[7] = copy[i + 1][j].rgbtBlue * 2;
            }

            if (check(i + 1, j - 1, height, width))
            {
                r[6] = 0;
                g[6] = 0;
                b[6] = 0;
            }
            else
            {
                r[6] = copy[i + 1][j - 1].rgbtRed * 1;
                g[6] = copy[i + 1][j - 1].rgbtGreen * 1;
                b[6] = copy[i + 1][j - 1].rgbtBlue * 1;
            }

            if (check(i, j - 1, height, width))
            {
                r[3] = 0;
                g[3] = 0;
                b[3] = 0;
            }
            else
            {
                r[3] = copy[i][j - 1].rgbtRed * 0;
                g[3] = copy[i][j - 1].rgbtGreen * 0;
                b[3] = copy[i][j - 1].rgbtBlue * 0;
            }

            if (check(i - 1, j - 1, height, width))
            {
                r[0] = 0;
                g[0] = 0;
                b[0] = 0;
            }
            else
            {
                r[0] = copy[i - 1][j - 1].rgbtRed * -1;
                g[0] = copy[i - 1][j - 1].rgbtGreen * -1;
                b[0] = copy[i - 1][j - 1].rgbtBlue * -1;
            }

            if (check(i + 1, j + 1, height, width))
            {
                r[8] = 0;
                g[8] = 0;
                b[8] = 0;
            }
            else
            {
                r[8] = copy[i + 1][j + 1].rgbtRed * 1;
                g[8] = copy[i + 1][j + 1].rgbtGreen * 1;
                b[8] = copy[i + 1][j + 1].rgbtBlue * 1;
            }

            if (check(i, j + 1, height, width))
            {
                r[5] = 0;
                g[5] = 0;
                b[5] = 0;
            }
            else
            {
                r[5] = copy[i][j + 1].rgbtRed * 0;
                g[5] = copy[i][j + 1].rgbtGreen * 0;
                b[5] = copy[i][j + 1].rgbtBlue * 0;
            }

            if (check(i - 1, j + 1, height, width))
            {
                r[2] = 0;
                g[2] = 0;
                b[2] = 0;
            }
            else
            {
                r[2] = copy[i - 1][j + 1].rgbtRed * -1;
                g[2] = copy[i - 1][j + 1].rgbtGreen * -1;
                b[2] = copy[i - 1][j + 1].rgbtBlue * -1;
            }

            int Gxr = 0;
            for (int c = 0; c < 9; c++)
            {
                Gxr += r[c];
            }

            int Gxg = 0;
            for (int c = 0; c < 9; c++)
            {
                Gxg += g[c];
            }

            int Gxb = 0;
            for (int c = 0; c < 9; c++)
            {
                Gxb += b[c];
            }

            // final values
            int red1 = roundoff(sqrt(GxR * GxR + Gxr * Gxr));
            int green1 = roundoff(sqrt(GxG * GxG + Gxg * Gxg));
            int blue1 = roundoff(sqrt(GxB * GxB + Gxb * Gxb));

            if (red1 > 255)
            {
                red1 = 255;
            }
            if (green1 > 255)
            {
                green1 = 255;
            }
            if (blue1 > 255)
            {
                blue1 = 255;
            }

            // Setting values of pixel
            image[i][j].rgbtRed = red1;
            image[i][j].rgbtGreen = green1;
            image[i][j].rgbtBlue = blue1;

            free(R);
            free(G);
            free(B);
            free(r);
            free(g);
            free(b);
        }
    }
    free(copy);
    return;
}

int roundoff(float e)
{
    int f = e;
    if (e - f < 0.5 || e - f == 0)
    {
        f += 0;
    }
    else if (e - f >= 0.5)
    {
        f += 1;
    }

    return f;
}

bool check(int a, int b, int height, int width)
{
    if (a < 0 || b < 0 || a >= height || b >= width)
    {
        return true;
    }
    else
    {
        return false;
    }
}
