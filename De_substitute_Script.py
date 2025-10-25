#Algorytm szyfru przesunięciowego (Cezara)
def szyfr(tekst, klucz):
    zaszyfrowany_tekst = ""
    
    for i in tekst:
        if i.islower() and i.isalpha():
                litera = ord(i) - klucz
                if litera < 97:
                    litera+=26
                    zaszyfrowany_tekst += chr(litera)
                else:
                    zaszyfrowany_tekst += chr(litera)

        elif i.isupper() and i.isalpha():
                litera = ord(i) - klucz
                if litera < 65:
                    litera+=26
                    zaszyfrowany_tekst += chr(litera)
                else:
                    zaszyfrowany_tekst += chr(litera)
        else:
             zaszyfrowany_tekst+=i
             
    print(zaszyfrowany_tekst)

tekst = """Ohuuh Rplzglr
“P aopur pa'z khyr huk pa svvrz sprl yhpu”
Fvb zhpk
“Huk aol dpuk pz isvdpun sprl pa'z aol luk vm aol dvysk”
Fvb zhpk
“Huk pa'z zv jvsk... sprl aol jvsk pm fvb dlyl klhk”
Huk aolu fvb ztpslk mvy h zljvuk

“P aopur P't vsk huk P't mllspun whpu”
Fvb zhpk
“Huk pa'z hss ybuupun vba sprl pa'z aol luk vm aol dvysk”
Fvb zhpk
“Huk pa'z zv jvsk... sprl aol jvsk pm fvb dlyl klhk”
Huk aolu fvb ztpslk mvy h zljvuk"""
     

szyfr(tekst, 7)