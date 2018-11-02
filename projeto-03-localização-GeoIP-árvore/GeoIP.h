/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeoIP.h
 * Author: schaiana
 *
 * Created on 10 de Junho de 2016, 09:59
 */

#ifndef GEOIP_H
#define GEOIP_H
#include "string.h"
#include "GeoIP.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace std;

class GeoIP {
public:
    GeoIP(const string & linha);
    GeoIP();
    GeoIP(const GeoIP& orig);
    GeoIP(const unsigned int& ip1, const unsigned int& ip2, unsigned int id);
    virtual ~GeoIP();
    unsigned int get_addr1() const;
    unsigned int get_addr2() const;
    unsigned int get_location() const;
    bool operator==(const GeoIP & outro) const;
    bool operator<(const GeoIP & outro) const;
    
    
    
private:
    unsigned int addr1, addr2; //inteiro sem sinal
    unsigned int locid;
};

ostream& operator<<(ostream & out, const GeoIP & geoIP);
class GeoIPLocation {
public:
    GeoIPLocation(const string & linha);
    GeoIPLocation();
    GeoIPLocation(unsigned int locid);
    GeoIPLocation(const GeoIPLocation & orig);
    virtual ~GeoIPLocation();
    unsigned int get_id() const;
    string get_pais() const;
    string get_regiao() const;
    string get_cidade() const;
    string get_zipcode() const;
    double get_latitude() const;
    double get_longitude() const;
    unsigned int get_metro() const;
    unsigned int get_area() const;
    bool operator==(const GeoIPLocation & outro) const;
    bool operator<(const GeoIPLocation & outro) const;
    
private:
    unsigned int id;
    string pais;
    string regiao;
    string cidade;
    string zipcode;
    double latitude, longitude;
    unsigned int metro, area;
}; 

ostream& operator<<(ostream & out, const GeoIPLocation & geoIPLoc);

#endif /* GEOIP_H */

