#ifndef KUTIL_H
#define KUTIL_H
/****************************************
*  Computer Algebra System SINGULAR     *
****************************************/
/* $Id: kutil.h,v 1.14 1999-05-26 16:23:56 obachman Exp $ */
/*
* ABSTRACT: kernel: utils for kStd
*/
#include "structs.h"
#include "mmemory.h"
#include "ring.h"
#include <string.h>

#define setmax 16

typedef int* intset;

struct sTObject{
                 poly  p;
                 int ecart,length;
               };
struct sLObject{
                 poly  p;
                 poly  p1,p2; /*- the pair p comes from -*/
                 poly  lcm;   /*- the lcm of p1,p2 -*/
                 int ecart,length;
               };
typedef struct sTObject TObject;
typedef struct sLObject LObject;
typedef TObject * TSet;
typedef LObject * LSet;

extern int HCord;

class skStrategy;
typedef skStrategy * kStrategy;
class skStrategy
{
  public:
    kStrategy next;
    void (*red)(LObject * L,kStrategy strat);
    void (*initEcart)(LObject * L);
    int (*posInT)(const TSet T,const int tl,const LObject &h);
    int (*posInL)(const LSet set, const int length,
                  const LObject &L,const kStrategy strat);
    void (*enterS)(LObject h, int pos,kStrategy strat);
    void (*initEcartPair)(LObject * h, poly f, poly g, int ecartF, int ecartG);
    int (*posInLOld)(const LSet Ls,const int Ll,
                     const LObject &Lo,const kStrategy strat);
    void (*spSpolyLoop)(poly p1, poly p2, poly m, poly spNoether);
    pFDegProc pOldFDeg;
    ideal Shdl;
    ideal D; /*V(S) is in D(D)*/
    ideal M; /*set of minimal generators*/
    polyset S;
    intset ecartS;
    intset fromQ;
    TSet T;
    LSet L;
    LSet    B;
    poly    kHEdge;
    poly    kNoether;
    BOOLEAN * NotUsedAxis;
    LObject P;
    poly tail;
    leftv kIdeal;
    intvec * kModW;
    intvec * kHomW;
    BOOLEAN *pairtest;/*used for enterOnePair*/
    int cp,c3;
    int sl,mu;
    int tl,tmax;
    int Ll,Lmax;
    int Bl,Bmax;
    int ak,LazyDegree,LazyPass;
    int syzComp;
    int HCord;
    int lastAxis;
    int newIdeal;
    int minim;
    BOOLEAN interpt;
    BOOLEAN homog;
    BOOLEAN kHEdgeFound;
    BOOLEAN honey,sugarCrit;
    BOOLEAN Gebauer,noTailReduction;
    BOOLEAN fromT;
    BOOLEAN noetherSet;
    BOOLEAN update;
    BOOLEAN posInLOldFlag;
           /*FALSE, if posInL == posInL10*/
    char    redTailChange;
    char    news;
    char    newt;/*used for messageSets*/
};

void deleteHC(poly *p, int *e, int *l, kStrategy strat);
void deleteInS (int i,kStrategy strat);
void cleanT (kStrategy strat);
LSet initL ();
void deleteInL(LSet set, int *length, int j,kStrategy strat);
void enterL (LSet *set,int *length, int *LSetmax, LObject p,int at);
void initEcartPairBba (LObject* Lp,poly f,poly g,int ecartF,int ecartG);
void initEcartPairMora (LObject* Lp,poly f,poly g,int ecartF,int ecartG);
int posInS (polyset set,int length,poly p);
int posInT0 (const TSet set,const int length,const LObject &p);
int posInT1 (const TSet set,const int length,const LObject &p);
int posInT2 (const TSet set,const int length,const LObject &p);
int posInT11 (const TSet set,const int length,const LObject &p);
int posInT13 (const TSet set,const int length,const LObject &p);
int posInT15 (const TSet set,const int length,const LObject &p);
int posInT17 (const TSet set,const int length,const LObject &p);
int posInT19 (const TSet set,const int length,const LObject &p);
void reorderS (int* suc,kStrategy strat);
int posInL0 (const LSet set, const int length,
             const LObject &L,const kStrategy strat);
int posInL11 (const LSet set, const int length,
             const LObject &L,const kStrategy strat);
int posInL13 (const LSet set, const int length,
             const LObject &L,const kStrategy strat);
int posInL15 (const LSet set, const int length,
             const LObject &L,const kStrategy strat);
int posInL17 (const LSet set, const int length,
             const LObject &L,const kStrategy strat);
poly redtailBba (poly p,int pos,kStrategy strat);
poly redtailSyz (poly p,int pos,kStrategy strat);
poly redtail (poly p,int pos,kStrategy strat);
void enterpairs (poly h, int k, int ec, int pos,kStrategy strat);
void entersets (LObject h);
void pairs ();
void message (int i,int* reduc,int* olddeg,kStrategy strat);
void messageStat (int srmax,int lrmax,int hilbcount,kStrategy strat);
void messageSets (kStrategy strat);
void initEcartNormal (LObject* h);
void initEcartBBA (LObject* h);
void initS (ideal F, ideal Q,kStrategy strat);
void initSL (ideal F, ideal Q,kStrategy strat);
void updateS(BOOLEAN toT,kStrategy strat);
void enterSBba (LObject p, int pos,kStrategy strat);
void enterT (LObject p,kStrategy strat);
void enterTBba (LObject p, int pos,kStrategy strat);
void cancelunit (LObject* p);
void HEckeTest (poly pp,kStrategy strat);
void redtailS (poly* h,int maxIndex);
void redtailMora (poly* h,int maxIndex);
void initBuchMoraCrit(kStrategy strat);
void initHilbCrit(ideal F, ideal Q, intvec **hilb,kStrategy strat);
void initBuchMoraPos(kStrategy strat);
void initBuchMora (ideal F, ideal Q,kStrategy strat);
void exitBuchMora (kStrategy strat);
void updateResult(ideal r,ideal Q,kStrategy strat);
void completeReduce (kStrategy strat);
BOOLEAN homogTest(polyset F, int Fmax);
BOOLEAN newHEdge(polyset S, int ak,kStrategy strat);

rOrderType_t spGetOrderType(ring r, int modrank, int syzcomp);
extern int spCheckCoeff(number *a, number *b);

inline TSet initT () { return (TSet)Alloc0(setmax*sizeof(TObject)); }
#ifdef KDEBUG
#define kTest(A) K_Test(__FILE__,__LINE__,A)
void K_Test(char *f, int i,kStrategy strat);
#else
#define kTest(A)
#endif
#endif
