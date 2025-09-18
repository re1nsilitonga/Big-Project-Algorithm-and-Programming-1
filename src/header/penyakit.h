#ifndef PENYAKIT_H
#define PENYAKIT_H

typedef struct
{
    int Id;
    char NamaPenyakit[50];
    float SuhuTubuhMin;
    float SuhuTubuhMax;
    int TekananDarahSistolikMin;
    int TekananDarahSistolikMax;
    int TekananDarahDiastolikMin;
    int TekananDarahDiastolikMax;
    int DetakJantungMin;
    int DetakJantungMax;
    float SaturasiOksigenMin;
    float SaturasiOksigenMax;
    int KadarGulaDarahMin;
    int KadarGulaDarahMax;
    float BeratBadanMin;
    float BeratBadanMax;
    int TinggiBadanMin;
    int TinggiBadanMax;
    int KadarKolesterolMin;
    int KadarKolesterolMax;
    int TrombositMin;
    int TrombositMax;
} Penyakit;

typedef struct
{
    Penyakit *data;
    int jumlah;
    int kapasitas;
} dataPenyakit;

#endif