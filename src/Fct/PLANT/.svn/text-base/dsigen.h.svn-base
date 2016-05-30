#ifndef _DSIGEN
#define _DSIGEN


#define FEED 1
#define BOTTOM -1
#define TOP -2

typedef struct
  {
  int name, bottom, top;
  } APPARAT;


typedef struct
  {
  char cut[10];
  double rank;
  } RANK;


typedef struct
  {
  char  alias[50];
  float mole_frac;
  } KOMP;


/********************************************************************/

void CreateRankTab (int No_of_Coeffs);
void SetRankTab (int act, char *name, double rank);
void RankSort (void);
void DeleteRankTab (void);

static char *Schnitt(char *stream);
static void SplitStream (char *fs, char *schnitt, char *ts, char *bs);
static void W2M (char *s, char *schnitt, int feed);
static void BuildMatrix (void);
int  Matrix (const int apparat, const int strom);


static void Stroeme (int apparat, int *feed, int *top, int *bottom);
static int Nachfolger (int apparat, char dir);
static void Produktsuche (APPARAT *apparat);
static void Matrix2Liste (void);
static void LightKey (int apparat, char *lightkey);

/********************************************************************/

int maxapparate;
int maxstroeme;
int maxcomps;

RANK *ranktab = NULL;
static int *matrix = NULL;
static int apparat;
static int strom;
static APPARAT *liste;
static Produkt;
/* maximale Stoffkomposition.
   Z geht nicht mehr als Stoffkomponente, da Z als 
   Platzhalter für die Topologieliste verwendet wird.
*/
static char components[30] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };


#endif  
