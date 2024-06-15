#define SCALES 7
#define NOTES  


void initP();
void piano();
void drawKey(int idx,uint32_t color);
static int notes[9][12]={
    {C0,D0b,D0,E0b,E0,F0,G0b,G0,A0b,A0,B0b,B0},
    {C1,D1b,D1,E1b,E1,F1,G1b,G1,A1b,A1,B1b,B1},
    {C2,D2b,D2,E2b,E2,F2,G2b,G2,A2b,A2,B2b,B2},
    {C3,D3b,D3,E3b,E3,F3,G3b,G3,A3b,A3,B3b,B3},
    {C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B},
    {C5,D5b,D5,E5b,E5,F5,G5b,G5,A5b,A5,B5b,B5},
    {C6,D6b,D6,E6b,E6,F6,G6b,G6,A6b,A6,B6b,B6},
    {C7,D7b,D7,E7b,E7,F7,G7b,G7,A7b,A7,B7b,B7},
    {C8,D8b,D8,E8b,E8,F8,G8b,G8,A8b,A8,B8b,B8},
};

void drawPiano(int i);