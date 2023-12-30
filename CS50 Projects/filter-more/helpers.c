#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            uint8_t Red = image[i][j].rgbtRed;
            uint8_t Green = image[i][j].rgbtGreen;
            uint8_t Blue = image[i][j].rgbtBlue;
            uint8_t avg = (uint8_t)(round((Red + Green + Blue) / 3.0));

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        int w = width - 1;
        for(int j = 0; j < width / 2; j++)
        {
            uint8_t r, g, b;
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][w].rgbtRed;
            image[i][j].rgbtGreen = image[i][w].rgbtGreen;
            image[i][j].rgbtBlue = image[i][w].rgbtBlue;

            image[i][w].rgbtRed = r;
            image[i][w].rgbtGreen = g;
            image[i][w].rgbtBlue = b;

            w--;
        }
    }
    return;
}

typedef struct
{
    int x;
    int y;
} Corner;

typedef int side;

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Check if edge
    // if true -> check if corner
    //   if true -> heck what side and act accordingly
    //   if false -> check what endge and act accordingly
    // if false -> act normal (3x3)

    RGBTRIPLE tmp[height][width];

    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            tmp[h][w] = image[h][w];
        }
    }

    Corner topLeft = {0,0};
    Corner topRight = {width - 1,0};
    Corner buttomLeft = {0,height - 1};
    Corner buttomRight = {width - 1, height - 1};

    const side top = 0;
    const side buttom = height - 1;
    const side left = 0;
    const side right = width - 1;

    const int cornerDivision = 4;
    const int sideDivision = 6;
    const int fullDivision = 9;

    int tR, tG, tB;
    int trR, trG, trB;
    int tlR, tlG, tlB;
    int ttR, ttG, ttB;
    int tbR, tbG, tbB;
    int tdR, tdG, tdB;
    int tdtR,tdtG, tdtB;
    int tdbR, tdbG, tdbB;
    int tdrR, tdrG, tdrB;
    int tdlR, tdlG, tdlB;
    int tdtlR, tdtlG, tdtlB;
    int tdblR, tdblG, tdblB;
    int tdtrR, tdtrG, tdtrB;
    int tdbrR, tdbrG, tdbrB;
    int avgR, avgG, avgB;

    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            if(w == topLeft.x && h == topLeft.y)
            {
                // h = 0 w = 0
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                trR = tmp[h][w + 1].rgbtRed;
                trG = tmp[h][w + 1].rgbtGreen;
                trB = tmp[h][w + 1].rgbtBlue;

                tbR = tmp[h + 1][w].rgbtRed;
                tbG = tmp[h + 1][w].rgbtGreen;
                tbB = tmp[h + 1][w].rgbtBlue;

                tdR = tmp[h + 1][w + 1].rgbtRed;
                tdG = tmp[h + 1][w + 1].rgbtGreen;
                tdB = tmp[h + 1][w + 1].rgbtBlue;

                avgR = (int)round(((tR + trR + tbR + tdR) / (double)cornerDivision));
                avgG = (int)round(((tG + trG + tbG + tdG) / (double)cornerDivision));
                avgB = (int)round(((tB + trB + tbB + tdB) / (double)cornerDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else if(w == topRight.x && h == topRight.y)
            {
                // h = 0 & w = width - 1

                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                tlR = tmp[h][w - 1].rgbtRed;
                tlG = tmp[h][w - 1].rgbtGreen;
                tlB = tmp[h][w - 1].rgbtBlue;

                tbR = tmp[h + 1][w].rgbtRed;
                tbG = tmp[h + 1][w].rgbtGreen;
                tbB = tmp[h + 1][w].rgbtBlue;

                tdR = tmp[h + 1][w - 1].rgbtRed;
                tdG = tmp[h + 1][w - 1].rgbtGreen;
                tdB = tmp[h + 1][w - 1].rgbtBlue;

                avgR = (int)round(((tR + tlR + tbR + tdR) / (double)cornerDivision));
                avgG = (int)round(((tG + tlG + tbG + tdG) / (double)cornerDivision));
                avgB = (int)round(((tB + tlB + tbB + tdB) / (double)cornerDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else if(w == buttomLeft.x && h == buttomLeft.y)
            {
                // h = height - 1 & w = 0
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                trR = tmp[h][w + 1].rgbtRed;
                trG = tmp[h][w + 1].rgbtGreen;
                trB = tmp[h][w + 1].rgbtBlue;

                ttR = tmp[h - 1][w].rgbtRed;
                ttG = tmp[h - 1][w].rgbtGreen;
                ttB = tmp[h - 1][w].rgbtBlue;

                tdR = tmp[h - 1][w + 1].rgbtRed;
                tdG = tmp[h - 1][w + 1].rgbtGreen;
                tdB = tmp[h - 1][w + 1].rgbtBlue;

                avgR = (int)round(((tR + trR + ttR + tdR) / (double)cornerDivision));
                avgG = (int)round(((tG + trG + ttG + tdG) / (double)cornerDivision));
                avgB = (int)round(((tB + trB + ttB + tdB) / (double)cornerDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else if(w == buttomRight.x && h == buttomRight.y)
            {
                // h = height - 1 & w = width - 1
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                tlR = tmp[h][w - 1].rgbtRed;
                tlG = tmp[h][w - 1].rgbtGreen;
                tlB = tmp[h][w - 1].rgbtBlue;

                ttR = tmp[h - 1][w].rgbtRed;
                ttG = tmp[h - 1][w].rgbtGreen;
                ttB = tmp[h - 1][w].rgbtBlue;

                tdR = tmp[h - 1][w - 1].rgbtRed;
                tdG = tmp[h - 1][w - 1].rgbtGreen;
                tdB = tmp[h - 1][w - 1].rgbtBlue;

                avgR = (int)round(((tR + tlR + ttR + tdR) / (double)cornerDivision));
                avgG = (int)round(((tG + tlG + ttG + tdG) / (double)cornerDivision));
                avgB = (int)round(((tB + tlB + ttB + tdB) / (double)cornerDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else if(h == top)
            {
                // h = 0 & 1 < w < width - 2
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                tlR = tmp[h][w - 1].rgbtRed;
                tlG = tmp[h][w - 1].rgbtGreen;
                tlB = tmp[h][w - 1].rgbtBlue;

                trR = tmp[h][w + 1].rgbtRed;
                trG = tmp[h][w + 1].rgbtGreen;
                trB = tmp[h][w + 1].rgbtBlue;

                tbR = tmp[h + 1][w].rgbtRed;
                tbG = tmp[h + 1][w].rgbtGreen;
                tbB = tmp[h + 1][w].rgbtBlue;

                tdlR = tmp[h + 1][w - 1].rgbtRed;
                tdlG = tmp[h + 1][w - 1].rgbtGreen;
                tdlB = tmp[h + 1][w - 1].rgbtBlue;

                tdrR = tmp[h + 1][w + 1].rgbtRed;
                tdrG = tmp[h + 1][w + 1].rgbtGreen;
                tdrB = tmp[h + 1][w + 1].rgbtBlue;

                avgR = (int)round(((tR + tlR + trR + tbR + tdlR + tdrR) / (double)sideDivision));
                avgG = (int)round(((tG + tlG + trG + tbG + tdlG + tdrG) / (double)sideDivision));
                avgB = (int)round(((tB + tlB + trB + tbB + tdlB + tdrB) / (double)sideDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else if(h == buttom)
            {
                // h = height - 1 & 1 < w < width - 2
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                tlR = tmp[h][w - 1].rgbtRed;
                tlG = tmp[h][w - 1].rgbtGreen;
                tlB = tmp[h][w - 1].rgbtBlue;

                trR = tmp[h][w + 1].rgbtRed;
                trG = tmp[h][w + 1].rgbtGreen;
                trB = tmp[h][w + 1].rgbtBlue;

                ttR = tmp[h - 1][w].rgbtRed;
                ttG = tmp[h - 1][w].rgbtGreen;
                ttB = tmp[h - 1][w].rgbtBlue;

                tdlR = tmp[h - 1][w - 1].rgbtRed;
                tdlG = tmp[h - 1][w - 1].rgbtGreen;
                tdlB = tmp[h - 1][w - 1].rgbtBlue;

                tdrR = tmp[h - 1][w + 1].rgbtRed;
                tdrG = tmp[h - 1][w + 1].rgbtGreen;
                tdrB = tmp[h - 1][w + 1].rgbtBlue;

                avgR = (int)round(((tR + tlR + trR + ttR + tdlR + tdrR) / (double)sideDivision));
                avgG = (int)round(((tG + tlG + trG + ttG + tdlG + tdrG) / (double)sideDivision));
                avgB = (int)round(((tB + tlB + trB + ttB + tdlB + tdrB) / (double)sideDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else if(w == left)
            {
                // 1 < h < height - 2 & w = 0
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                ttR = tmp[h - 1][w].rgbtRed;
                ttG = tmp[h - 1][w].rgbtGreen;
                ttB = tmp[h - 1][w].rgbtBlue;

                tbR = tmp[h + 1][w].rgbtRed;
                tbG = tmp[h + 1][w].rgbtGreen;
                tbB = tmp[h + 1][w].rgbtBlue;

                trR = tmp[h][w + 1].rgbtRed;
                trG = tmp[h][w + 1].rgbtGreen;
                trB = tmp[h][w + 1].rgbtBlue;

                tdtR = tmp[h - 1][w + 1].rgbtRed;
                tdtG = tmp[h - 1][w + 1].rgbtGreen;
                tdtB = tmp[h - 1][w + 1].rgbtBlue;

                tdbR = tmp[h + 1][w + 1].rgbtRed;
                tdbG = tmp[h + 1][w + 1].rgbtGreen;
                tdbB = tmp[h + 1][w + 1].rgbtBlue;

                avgR = (int)round((((tR + ttR + tbR + trR + tdtR + tdbR) / (double)sideDivision)));
                avgG = (int)round((((tG + ttG + tbG + trG + tdtG + tdbG) / (double)sideDivision)));
                avgB = (int)round((((tB + ttB + tbB + trB + tdtB + tdbB) / (double)sideDivision)));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;

            }
            else if(w == right)
            {
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                ttR = tmp[h - 1][w].rgbtRed;
                ttG = tmp[h - 1][w].rgbtGreen;
                ttB = tmp[h - 1][w].rgbtBlue;

                tbR = tmp[h + 1][w].rgbtRed;
                tbG = tmp[h + 1][w].rgbtGreen;
                tbB = tmp[h + 1][w].rgbtBlue;

                tlR = tmp[h][w - 1].rgbtRed;
                tlG = tmp[h][w - 1].rgbtGreen;
                tlB = tmp[h][w - 1].rgbtBlue;

                tdtR = tmp[h - 1][w - 1].rgbtRed;
                tdtG = tmp[h - 1][w - 1].rgbtGreen;
                tdtB = tmp[h - 1][w - 1].rgbtBlue;

                tdbR = tmp[h + 1][w - 1].rgbtRed;
                tdbG = tmp[h + 1][w - 1].rgbtGreen;
                tdbB = tmp[h + 1][w - 1].rgbtBlue;

                avgR = (int)round(((tR + ttR + tbR + tlR + tdtR + tdbR) / (double)sideDivision));
                avgG = (int)round(((tG + ttG + tbG + tlG + tdtG + tdbG) / (double)sideDivision));
                avgB = (int)round(((tB + ttB + tbB + tlB + tdtB + tdbB) / (double)sideDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
            else
            {
                tR = tmp[h][w].rgbtRed;
                tG = tmp[h][w].rgbtGreen;
                tB = tmp[h][w].rgbtBlue;

                tlR = tmp[h][w - 1].rgbtRed;
                tlG = tmp[h][w - 1].rgbtGreen;
                tlB = tmp[h][w - 1].rgbtBlue;

                trR = tmp[h][w + 1].rgbtRed;
                trG = tmp[h][w + 1].rgbtGreen;
                trB = tmp[h][w + 1].rgbtBlue;

                ttR = tmp[h - 1][w].rgbtRed;
                ttG = tmp[h - 1][w].rgbtGreen;
                ttB = tmp[h - 1][w].rgbtBlue;

                tbR = tmp[h + 1][w].rgbtRed;
                tbG = tmp[h + 1][w].rgbtGreen;
                tbB = tmp[h + 1][w].rgbtBlue;

                tdtlR = tmp[h - 1][w - 1].rgbtRed;
                tdtlG = tmp[h - 1][w - 1].rgbtGreen;
                tdtlB = tmp[h - 1][w - 1].rgbtBlue;

                tdblR = tmp[h + 1][w - 1].rgbtRed;
                tdblG = tmp[h + 1][w - 1].rgbtGreen;
                tdblB = tmp[h + 1][w - 1].rgbtBlue;

                tdtrR = tmp[h - 1][w + 1].rgbtRed;
                tdtrG = tmp[h - 1][w + 1].rgbtGreen;
                tdtrB = tmp[h - 1][w + 1].rgbtBlue;

                tdbrR = tmp[h + 1][w + 1].rgbtRed;
                tdbrG = tmp[h + 1][w + 1].rgbtGreen;
                tdbrB = tmp[h + 1][w + 1].rgbtBlue;

                avgR = (int)round(((tR + ttR + tbR + trR + tlR + tdtlR + tdblR + tdtrR + tdbrR) / (double)fullDivision));
                avgG = (int)round(((tG + ttG + tbG + trG + tlG + tdtlG + tdblG + tdtrG + tdbrG) / (double)fullDivision));
                avgB = (int)round(((tB + ttB + tbB + trB + tlB + tdtlB + tdblB + tdtrB + tdbrB) / (double)fullDivision));

                image[h][w].rgbtRed = avgR;
                image[h][w].rgbtGreen = avgG;
                image[h][w].rgbtBlue = avgB;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
