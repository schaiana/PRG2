/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GeoIP.cpp
 * Author: schaiana
 * 
 * Created on 10 de Junho de 2016, 09:59
 */

#include "GeoIP.h"


//fazer com sscanf
//"16777216","16777471","17"
GeoIP::GeoIP(const string & linha){ //o construtor retorna 
    istringstream inp(linha);
    
    inp.ignore(1);
    inp >> addr1;
    inp.ignore(3);
    inp >> addr2;
    inp.ignore(3);
    inp >> locid;
    
    if (inp.fail()) throw -1; //diz se alguma operação falhou, qualquer uma delas
    
    
}

GeoIP::GeoIP() {
}

GeoIP::GeoIP(const unsigned int& ip1, const unsigned int& ip2, unsigned int id) {
    addr1 = ip1;
    addr2 = ip2;
    locid = id;
}

GeoIP::GeoIP(const GeoIP& orig) {
}

GeoIP::~GeoIP() {
}

unsigned int GeoIP::get_addr1() const {
   
 return addr1;
 
}
unsigned int GeoIP::get_addr2() const {
  
 return addr2;

}

unsigned int GeoIP::get_location() const {
    
    return locid;

}

ostream& operator<<(ostream & out, const GeoIP & geoIP) {
    out << "\"" << geoIP.get_addr1() << "\",\"" << geoIP.get_addr2() << "\",\"" << geoIP.get_location() << "\"";
    return out;
}



/*locId,country,region,city,postalCode,latitude,longitude,metroCode,areaCode
1,"O1","","","",0.0000,0.0000,,*/


bool GeoIP::operator<(const GeoIP & outro) const {
    if (addr1 < outro.addr1){
        return true;
    } 
    return false;
}

bool GeoIP::operator==(const GeoIP& outro) const {
    // verdadeiro se a faixa de endereços do "outro" objeto GeoIP estiver dentro 
    // da faixa de endereços deste objeto GeoIP
    bool ok = addr1 <= outro.addr1 and addr2 >= outro.addr2;
 
    // verdadeiro se a faixa de endereços deste objeto estiver dentro 
    // da faixa de endereços do "outro" (só necessário testar se ok for false)
    if (not ok) ok = addr1 >= outro.addr1 and addr2 <= outro.addr2;
 
    return ok;
}

GeoIPLocation::GeoIPLocation() {
  
}

GeoIPLocation::GeoIPLocation(const string & linha){
    istringstream inp(linha);
    char textoTemp[50];
    
    inp >> id;
    inp.ignore(2);
    inp.get(textoTemp, 100, '"');
    pais = textoTemp;
    
    inp.ignore(3);
    if(inp.peek()=='"'){
        regiao = "";
    } else {
        inp.get(textoTemp, 100, '"');
        regiao = textoTemp;
    }
    
    inp.ignore(3);
    if(inp.peek()=='"'){
        cidade = "";
    } else {
        inp.get(textoTemp, 100, '"');
        cidade = textoTemp;
    }
    
    inp.ignore(3);
    if(inp.peek()=='"'){
        zipcode = "";
    } else {
        inp.get(textoTemp, 100, '"');
        zipcode = textoTemp;
    }
    
    inp.ignore(2);
    inp >> latitude;
    inp.ignore(1);
    inp >> longitude;
    inp.ignore(1);
    
    if (inp.peek() == ','){
        metro = 0;
    } else {
        inp >> metro;
        
    }
    
   
    inp.ignore(1);
    
    if (inp.peek() == -1){
        area = 0;
    } else {
        inp >> area;
        
    }
    
    
    if (inp.fail()) throw -1; //diz se alguma operação falhou, qualquer uma delas
       

}

GeoIPLocation::GeoIPLocation(unsigned int locid) {
    id = locid;
}


GeoIPLocation::GeoIPLocation(const GeoIPLocation& orig) {
}

GeoIPLocation::~GeoIPLocation() {
}

unsigned int GeoIPLocation::get_id() const{
    return id;    
}

string GeoIPLocation::get_pais() const{
   return pais; 
}

string GeoIPLocation::get_regiao() const{
    return regiao;
}

string GeoIPLocation::get_cidade() const{
    return cidade;
}

string GeoIPLocation::get_zipcode() const{
    return zipcode;
}

double GeoIPLocation::get_latitude() const{
    return latitude;    
}

double GeoIPLocation::get_longitude() const{
    return longitude;    
}

unsigned int GeoIPLocation::get_metro() const{
    return metro;
}

unsigned int GeoIPLocation::get_area() const{
    return area;
}


bool GeoIPLocation::operator==(const GeoIPLocation & outro) const {
    if (id == outro.id){
        return true;
    } 
    return false;
}



bool GeoIPLocation::operator<(const GeoIPLocation & outro) const {
    if (id < outro.id){
        return true;
    } 
    return false;
}

ostream& operator<<(ostream & out, const GeoIPLocation & geoIPLoc) {
    out << geoIPLoc.get_id() << ",\"" << geoIPLoc.get_pais() << "\",\"" << geoIPLoc.get_regiao() << "\",\"";
    out << geoIPLoc.get_cidade() << "\",\"" << geoIPLoc.get_zipcode() << "\"," << geoIPLoc.get_latitude() << ",";
    out << geoIPLoc.get_longitude() << "," << geoIPLoc.get_metro() << "," << geoIPLoc.get_area();
    return out;
}

