Nume: Filimon Adrian
Grupă: 334CC

# Tema 1 - C Preprocessor

Organizare
-

- Pentru stocarea asocierilor dintre simboluri am folosit o structura de tip hashtable
- Structura contine o cheie si o valoare de tip char* si un pointer catre urmatorul element (in cazul in care apar coliziuni, se va folosi o lista simplu inlantuita)
- Tabela contine un numar fix de bucket-uri(definit static), dar listele sunt alocate dinamic
```
typedef struct entry_t {
	char *key;
	char *value;
	struct entry_t *next;
} entry_t;

typedef struct h_table {
	entry_t **entries;
} h_table;
```

- pentru a path-urile date ca parametru si cuvintele din fisiere, am folosit o alta structura **vector** -  un array de string-uri cu alocare dinamica

- abordarea este una destul de simpla:
    - se citeste linie cu linie din fisier si se face split in 2 vectori:
        - primul separa doar dupa newline si spatii(pentru directive)
        - al doilea separa si dupa alte caractere(paranteze, operatori etc.)
   - in functie de primul cuvant de pe linie se incearca o procesare:
       - daca este define, se incearca introducerea unui pair in tabela
       - daca if/else sunt verificate conditiile si se citesc/defines instructiuni in continuare sau se face skip
       - daca este include, se cauta fisierul respectiv si se incearca citirea fisierului respectiv(daca aceasta exista)
       - in ultima instanta, ramane codul din functii, unde doar se cauta mapari de cheie-valoare

- Tema a fost utila pentru reamintirea unor concepte de baza legate de pointeri si structuri de date. Cu toate aceastea, cred ca a fost destul de plictisitoare, nu a fost nimic deosebit la ea. Este doar o parsare de text, nimic iesit din comun. 

- Implementarea este una destul de ineficienta, sunt destul sigur ca se putea face mult mai usor si fara batai de cap. Am incercat sa programez putin mai high level, dar in mod evident au aparut penalizarile de performanta(viteza si memorie). Cred ca cerinta a fost putin ambigua si a trebuit sa mai restructurez parti din cod pe parcurs, ceea ce se si observa in design-ul functiilor

Implementare
-

- nu am reusit sa rezolv ultima cerinta, cea cu fail-ul la alocarile de memorie
    - codul este scris, daca rulez manual, totul este afisat cum trebuie si nu apar probleme cu alocarile
    - din pacate, pe checker nu functioneaza. Pe windows primesc fail, pe windows ramane agatat si nu se opreste
- de asemenea nu am implementat partea cu define-uri pe mai multe linii

- uneori primesc o eroare pe linux legata de coding style:
`./parser.h:9: ERROR:SPACING: need consistent spacing around '*' (ctx:WxV)`

Cum se compilează și cum se rulează?
-
### Semnatura functiei
* `so-cpp [-D <SYMBOL>[=<MAPPING>]] [-I <DIR>] [<INFILE>] [ [-o] <OUTFILE>]`

Bibliografie
-
- Hash function: http://www.cse.yorku.ca/~oz/hash.html


