#include "doomnukem.h"

//------------------------------------------------------------------------------
//--------------------------Code By: 3DSage-------------------------------------
//----------------Video tutorial on YouTube-3DSage------------------------------
//------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>

#define res        1                        //0=160x120 1=360x240 4=640x480
#define SW         800                  //screen width
#define SH         600                  //screen height
#define SW2        (SW/2)                   //half of screen width
#define SH2        (SH/2)                   //half of screen height
#define pixelScale 4/res                    //OpenGL pixel scale
#define GLSW       (SW*pixelScale)          //OpenGL window width
#define GLSH       (SH*pixelScale)          //OpenGL window height
#define numSect 4
#define numWall 16

//------------------------------------------------------------------------------

typedef struct 
{
 int w,s,a,d;           //move up, down, left, right
 int sl,sr;             //strafe left, right 
 int m;                 //move up, down, look up, down
}keys; keys K;
//------------------------------------------------------------------------------

typedef struct
{
    float cos[360];
    float sin[360];

}math; math M;

typedef struct 
{
    int x1,y1;
    int x2,y2;
    int c;

}t_walls; t_walls walls[30];

typedef struct 
{
    int ws, we;
    int z1, z2;
    int x, y;
    int d;
    int c1, c2;
    int surf[SW];
    int surface;
}t_sectors; t_sectors sectors[30];

void pixel(int x,int y, int c, t_prm *prm)                  //draw a pixel at x/y with rgb
{
int rgb[3];
 if(c==0){ rgb[0]=255; rgb[1]=255; rgb[2]=  0;} //Yellow	
 if(c==1){ rgb[0]=160; rgb[1]=160; rgb[2]=  0;} //Yellow darker	
 if(c==2){ rgb[0]=  0; rgb[1]=255; rgb[2]=  0;} //Green	
 if(c==3){ rgb[0]=  0; rgb[1]=160; rgb[2]=  0;} //Green darker	
 if(c==4){ rgb[0]=  0; rgb[1]=255; rgb[2]=255;} //Cyan	
 if(c==5){ rgb[0]=  0; rgb[1]=160; rgb[2]=160;} //Cyan darker
 if(c==6){ rgb[0]=160; rgb[1]=100; rgb[2]=  0;} //brown	
 if(c==7){ rgb[0]=110; rgb[1]= 50; rgb[2]=  0;} //brown darker
 if(c==8)
 { 
    rgb[0]=  0; rgb[1]= 60; rgb[2]=130;
} //background 
if (x > 0 && y > 0 && x < SW && y < SH)
    ((unsigned int *)prm->mlx->image_add)[(prm->mlx->size_line / 4) * y + x] = ((rgb[0]&0x0ff)<<16)|((rgb[1]&0x0ff)<<8)|(rgb[2]&0x0ff);
}

void movePlayer(t_player *player)
{
 //move up, down, left, right
 if(player->wasd[A] ==1 && player->m ==0){ player->a -= 4; if(player->a < 0) {player->a += 360;}}  
 if(player->wasd[D] ==1 && player->m ==0){ player->a += 4; if (player->a > 359) {player->a-=360;}}
 int dx=M.sin[player->a]*10.0;
 int dy=M.cos[player->a]*10.0;
 if(player->wasd[W] ==1 && player->m ==0)
 { player->x +=dx; player->y += dy; }
 if(player->wasd[S] ==1 && player->m ==0)
 { player->x -=dx; player->y -= dy; }

 //strafe left, right
 if(player->sr==1){ player->x += dy; player->y -= dx;}
 if(player->sl==1){ player->x -= dy; player->y += dx;}
 //move up, down, look up, look down
 if(player->wasd[A] ==1 && player->m==1){ player->l -= 1;}
 if(player->wasd[D] ==1 && player->m==1){ player->l += 1;}
 if(player->wasd[W] ==1 && player->m==1){ player->z -= 4;}
 if(player->wasd[S] ==1 && player->m==1){ player->z += 4;}
}

void clipBehindPlayer(int *x1, int *y1, int *z1, int x2, int y2, int z2)
{
    float da = *y1;
    float db = y2;
    float d = da-db; if (d==0){d=1;}
    float s = da/ (da-db);
    *x1 = *x1 + s*(x2-(*x1));
    *y1 = *y1 + s*(y2-(*y1)); if (*y1==0){*y1 = 1;}
    *z1 = *z1 + s*(z2-(*z1));
}

int dist(int x1, int y1, int x2, int y2)
{
    int distance = sqrt( (x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));
    return distance;
}

void drawWall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, t_prm *prm)
{
    int x, y;
    int dyb = b2-b1;
    int dyt = t2-t1;
    int dx = x2-x1; if (dx == 0){dx = 1;}
    int xs = x1;

    if (x1< 1){x1 = 1;}
    if (x2 < 1){x2 = 1;}
    if (x1>SW-1){x1=SW-1;}
    if (x2>SW-1){x2 = SW-1;}
    for (x=x1; x < x2; x++)
    {
        int y1 = dyb * (x-xs + 0.5) / dx + b1;
        int y2 = dyt * (x-xs + 0.5) / dx + t1;

        if (y1 < 1){y1 = 1;}
        if (y2 < 1){y2 = 1;}
        if (y1 > SH-1){y1 = SH-1;}
        if (y2 > SH-1){y2 = SH-1;}

        if (sectors[s].surface == 1) {sectors[s].surf[x]=y1; continue;}
        if (sectors[s].surface == 2) {sectors[s].surf[x]=y2; continue;}
        if (sectors[s].surface == -1) {for(y=sectors[s].surf[x];y<y1;y++){pixel(x, y, sectors[s].c1, prm);};}
        if (sectors[s].surface == -2) {for(y=y2;y<sectors[s].surf[x];y++){pixel(x, y, sectors[s].c2, prm);};}
        for (y = y1; y < y2; y++)
        {
            pixel(x, y, c, prm);
        }
        if (prm->player->slowspeed == 1)
        {
            mlx_put_image_to_window(prm->mlx->mlx_ptr, prm->mlx->win_ptr, prm->mlx->image_ptr, 0, 0);
            mlx_do_sync(prm->mlx->mlx_ptr);
            usleep(10000);
        }
    }

}

void draw3D(t_prm *prm)
{
    t_player *player;
    player = prm->player;
    int loop, s, w, wx[4], wy[4], wz[4]; float CS=M.cos[player->a], SN=M.sin[player->a];
    
    for (s=0;s<numSect-1;s++)
    {
        for(w=0;w<numSect-s-1;w++)
        {
            if (sectors[w].d < sectors[w + 1].d)
            {
                t_sectors st = sectors[w]; sectors[w]=sectors[w + 1]; sectors[w + 1] = st;
            }
        }
    }
    for (s=0;s<numSect;s++)
    {
        sectors[s].d = 0;
        if (player->z<sectors[s].z1) {sectors[s].surface = 1;}
        else if (player->z > sectors[s].z2) {sectors[s].surface = 2;}
        else {sectors[s].surface = 0;}
        for (loop = 0; loop < 2; loop++)
        {
            for (w = sectors[s].ws;w<sectors[s].we;w++)
            {
                int x1= walls[w].x1-player->x, y1 = walls[w].y1 - player->y;
                int x2 = walls[w].x2 - player->x, y2 = walls[w].y2-player->y;

                if (loop == 0)
                {
                    int swp=x1; x1=x2; x2=swp; swp=y1; y1=y2; y2=swp;
                }
                wx[0] = x1*CS-y1*SN;
                wx[1] = x2*CS-y2*SN;
                wx[2] = wx[0];
                wx[3] = wx[1];
                
                wy[0] = y1 * CS + x1 * SN;
                wy[1] = y2 * CS + x2 * SN;
                wy[2] = wy[0];
                wy[3] = wy[1];
                sectors[s].d +=dist(0,0, (wx[0]+wx[1])/2, (wy[0]+wy[1])/2);

                wz[0] = sectors[s].z1-player->z + ((player->l*wy[0])/32.0);
                wz[1] = sectors[s].z1-player->z + ((player->l*wy[1])/32.0);
                wz[2] = wz[0] + sectors[s].z2;
                wz[3] = wz[1] + sectors[s].z2;

                if (wy[0] < 1 && wy[1] < 1)
                    continue;
                if (wy[0] < 1)
                {
                    clipBehindPlayer(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);
                    clipBehindPlayer(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);
                }

                if (wy[1] < 1)
                {
                    clipBehindPlayer(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);
                    clipBehindPlayer(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);
                }

                wx[0] = wx[0] * 200/wy[0] + SW2; wy[0] = wz[0] * 200/wy[0] + SH2;
                wx[1] = wx[1] * 200/wy[1] + SW2; wy[1] = wz[1] * 200/wy[1] + SH2;
                wx[2] = wx[2] * 200/wy[2] + SW2; wy[2] = wz[2] * 200/wy[2] + SH2;
                wx[3] = wx[3] * 200/wy[3] + SW2; wy[3] = wz[3] * 200/wy[3] + SH2;
                drawWall(wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], walls[w].c, s, prm);
            }
            sectors[s].d/=(sectors[s].we-sectors[s].ws);
            sectors[s].surface*=-1;
        }
    }
}

int	mlx_window_loop(void *ptr)
{
	t_prm	*prm;
	t_mlx	*mlx;

	prm = ((t_prm *) ptr);
	mlx = prm->mlx;
    bzero(mlx->image_add, sizeof(unsigned int) * 800 * 600);
    movePlayer(prm->player);
    draw3D(prm);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image_ptr, 0, 0);
	mlx_do_sync(mlx->mlx_ptr);
    if (prm->player->slowspeed == 0)
    {
        usleep(50000);
    }
	return (0);
}

int loadSectors[]=
{
    0, 4, 0, 40, 2, 3,
    4, 8, 0, 40, 4, 5,
    8, 12, 0, 40, 6, 7,
    12, 16, 0, 40, 0, 1,
};

int loadWalls[]=
{
    0, 0, 32, 0, 0,
    32, 0, 32,32, 1,
    32,32, 0, 32, 0,
    0, 32, 0, 0, 1,
    
    64, 0, 96, 0, 2,
    96, 0, 96, 32, 3,
    96, 32, 64, 32, 2,
    64, 32, 64, 0, 3,

    64, 64, 96, 64, 4,
    96, 64, 96, 96, 5,
    96, 96, 64, 96, 4,
    64, 96, 64, 64, 5,

    0, 64, 32, 64, 6,
    32, 64, 32, 96, 7,
    32, 96, 0, 96, 6,
    0, 96, 0, 64, 7,
};

void init(t_prm *prm)
{       
    t_player *player;

    player = prm->player;
    int x;
    for (x = 0; x < 360; x++)
    {
        M.cos[x] = cos(x/180.0*M_PI);
        M.sin[x] = sin(x/180.0*M_PI);
    }
    player->x = 70;
    player->y = -110;
    player->z = 20;
    player->a = 0;
    player->l = 0;
    player->slowspeed = 0;

    int s, w, v1=0, v2=0;
    for (s = 0; s<numSect;s++)
    {
        sectors[s].ws=loadSectors[v1+0];
        sectors[s].we=loadSectors[v1+1];
        sectors[s].z1=loadSectors[v1+2];
        sectors[s].z2=loadSectors[v1+3]-loadSectors[v1 + 2];
        sectors[s].c1=loadSectors[v1+4];
        sectors[s].c2=loadSectors[v1+5];
        v1+=6;
        for (w=sectors[s].ws; w < sectors[s].we;w++)
        {
            walls[w].x1 = loadWalls[v2+0];
            walls[w].y1 = loadWalls[v2+1];
            walls[w].x2 = loadWalls[v2+2];
            walls[w].y2 = loadWalls[v2+3];
            walls[w].c = loadWalls[v2+4];
            v2+=5;
        }
    }
}

int main()
{
    t_prm prm;
    t_mlx mlx;
    t_player player;


    bzero(&prm, sizeof(t_prm));
    bzero(&mlx, sizeof(t_mlx));
    bzero(&player, sizeof(t_player));
    prm.mlx = &mlx;
    prm.player = &player;
    init(&prm);
    open_window(&prm);

    return(0);
}