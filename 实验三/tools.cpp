#include <string.h>
#include "tools.h"

template <class T>
void swap(T &a, T &b)
{
	T t = a;
	a = b;
	b = t;
}

int gltRound(double x)
{
	return x > 0 ? (int)(x+0.5) : (int)(x-0.5);
}

int gltTrunc(double x)
{
	return (int)x;
}

void gltRasterText(double x, double y, const char *text, void *font)
{
    if(text == NULL) return ;
    
    glRasterPos2d(x, y);
    for(int i=0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, text[i]);
    } 
}

void gltLine2i(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
    glEnd();
}

void gltRect2i(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y0);
	
	glVertex2i(x1, y0);
	glVertex2i(x1, y1);
	
	glVertex2i(x1, y1);
	glVertex2i(x0, y1);
	
	glVertex2i(x0, y1);
	glVertex2i(x0, y0);
    glEnd();
}

void gltLine2d(double x0, double y0, double x1, double y1)
{
    glBegin(GL_LINES);
        glVertex2d(x0, y0);
        glVertex2d(x1, y1);
    glEnd();
}

void gltRect2d(double x0, double y0, double x1, double y1)
{
    glBegin(GL_LINES);
        glVertex2d(x0, y0);
        glVertex2d(x1, y0);
        
        glVertex2d(x1, y0);
        glVertex2d(x1, y1);
        
        glVertex2d(x1, y1);
        glVertex2d(x0, y1);
        
        glVertex2d(x0, y1);
        glVertex2d(x0, y0);
    glEnd();
}

bool gltPtInPolygon(int x, int y, const GPoint2i *points, int n)
{
	return false;
}

struct EdgeNode     // �߽ڵ� 
{
	int yMax;
	double x, invk;
	EdgeNode *next;
	
	EdgeNode()
	{
		yMax = 0;
		x = 0;
		invk = 0;
		next = 0;
	}
};

void gltFillPolygon(const GPoint2i *points, int n)
{
    // int i, j, iy, min, max, xm, nc;
	// static int xs[256];
	// GPoint2i pt0, pt1;
	// if(n < 3) return ;
	// // 寻找扫描线范围
	// min = max = points[0].y();
	// for(i=1; i<n; i++)
	// {
	// 	if(min > points[i].y()) min = points[i].y();
	// 	if(max < points[i].y()) max = points[i].y();
	// }
	// for(iy=min; iy<=max; iy++)
	// {
	// 	// (1)用当前扫描线 y = iy 与多边形各条边求交, 记录交点
	// 	nc = 0;
	// 	for(i=0; i<n; i++)
	// 	{
	// 		pt0 = points[i];
	// 		pt1 = points[(i+1)%n];
	// 		// 跳过水平边
	// 		if(pt0.y() == pt1.y()) continue ;
	// 		if(pt0.y() > pt1.y()) swap(pt0, pt1);
	// 		// 如果扫描线不在边有效范围跳过
	// 		if(iy < pt0.y() || iy >= pt1.y()) continue ;
	// 		// 计算交点 x 坐标
	// 		xm = pt0.x()+(iy-pt0.y()) *
	// 		(pt1.x()-pt0.x())/(pt1.y()-pt0.y());
	// 		// 有序插入交点 x 坐标
	// 		for(j=nc-1; j>=0; j--)
	// 		{
	// 			if(xs[j] <= xm) break ;
	// 			xs[j+1] = xs[j];
	// 		}
	// 		xs[j+1] = xm;
	// 		nc++;
	// 		// 如果交点个数太多跳出
	// 		if(nc == 256) break;
	// 	}
	// 	// 配对填充
	// 	for(i=0; i<nc; i+=2)
	// 	{
	// 		gltLine2i(xs[i], iy, xs[i+1], iy);
	// 	}
	// }
	if(n < 3) return ;
	int i, index;
	int min, max;
	EdgeNode **edgeBucket; // 边表桶
	EdgeNode *p, *q, *pEdge, *aet;
	GPoint2i pt0, pt1, pt;
	// 寻找多边形 Y 方向扫描范围
	min = max = points[0].y();
	for(i=1; i<n; i++)
	{
		pt = points[i];
		if(min > (int)pt.y()) min = (int)pt.y();
		if(max < (int)pt.y()) max = (int)pt.y();
	}
	// 建立边表桶
	edgeBucket = new EdgeNode *[max-min+1];
	memset(edgeBucket, 0, sizeof(EdgeNode *)*(max-min+1));
	// 加入边节点到桶中
	for(i=0; i<n; i++)
	{
		pt0 = points[i];
		pt1 = points[(i+1)%n];
		// 跳过水平边
		if(pt0.y() == pt1.y()) continue;
		pEdge = new EdgeNode;
		if(pt0.y() > pt1.y()) // 保证 pt0 为 y 值较小端
		{
			pt = pt0;
			pt0 = pt1;
			pt1 = pt;
		}
		pEdge->yMax = pt1.y();
		pEdge->x = pt0.x();
		pEdge->invk = (double)(pt1.x()-pt0.x()) / (pt1.y()-pt0.y());
		// 边表项插入链表头部
		index = pt0.y() - min;
		pEdge->next = edgeBucket[index];
		edgeBucket[index] = pEdge;
	}
	
	// 扫描填充
	aet = new EdgeNode;
	for(i=min; i<=max; i++)
	{
		// (1)删除 y=ymax 的边项
		p = aet;
		while(p->next != 0)
		{
			pEdge = p->next;
			if(pEdge->yMax == i)
			{
				p->next = pEdge->next;
				delete pEdge;
			}
			else p = p->next;
		}
		// (2)将边表桶中的边表表项加入活动边表
		index = i - min;
		p = edgeBucket[index];
		while(p != 0)
		{
			pEdge = p;
			p = p->next;
			q = aet;
			while(q->next != 0)
			{
				if((int)q->next->x > (int)pEdge->x) break ;
				else if((int)q->next->x == (int)pEdge->x)
				{
					if(q->next->invk > pEdge->invk) break ;
				}
				q = q->next;
			}
			pEdge->next = q->next;
			q->next = pEdge;
		}
		// (3)配对填充
		p = aet->next;
		while(p != 0)
		{
			gltLine2i(p->x, i, p->next->x, i);
			p = p->next->next;
		}
		// (4)修改 AET 表项, 增加 x 值
		p = aet->next;
		while(p != 0)
		{
			p->x += p->invk;
			p = p->next;
		}
	}
	// 释放剩余内存
	delete aet;
	delete []edgeBucket;
}
