
/* c401.c: **********************************************************}
{* Téma: Rekurzivní implementace operací nad BVS
**                                         Vytvoøil: Petr Pøikryl, listopad 1994
**                                         Úpravy: Andrea Nìmcová, prosinec 1995
**                                                      Petr Pøikryl, duben 1996
**                                                   Petr Pøikryl, listopad 1997
**                                  Pøevod do jazyka C: Martin Tuèek, øíjen 2005
**                                         Úpravy: Bohuslav Køena, listopad 2009
**                                         Úpravy: Karel Masaøík, øíjen 2013
**                                         Úpravy: Radek Hranický, øíjen 2014
**
** Implementujte rekurzivním zpùsobem operace nad binárním vyhledávacím
** stromem (BVS; v angliètinì BST - Binary Search Tree).
**
** Klíèem uzlu stromu je jeden znak (obecnì jím mù¾e být cokoliv, podle
** èeho se vyhledává). U¾iteèným (vyhledávaným) obsahem je zde integer.
** Uzly s men¹ím klíèem le¾í vlevo, uzly s vìt¹ím klíèem le¾í ve stromu
** vpravo. Vyu¾ijte dynamického pøidìlování pamìti.
** Rekurzivním zpùsobem implementujte následující funkce:
**
**   BSTInit ...... inicializace vyhledávacího stromu
**   BSTSearch .... vyhledávání hodnoty uzlu zadaného klíèem
**   BSTInsert .... vkládání nové hodnoty
**   BSTDelete .... zru¹ení uzlu se zadaným klíèem
**   BSTDispose ... zru¹ení celého stromu
**
** ADT BVS je reprezentován koøenovým ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje klíè (typu char), podle
** kterého se ve stromu vyhledává, vlastní obsah uzlu (pro jednoduchost
** typu int) a ukazatel na levý a pravý podstrom (LPtr a RPtr). Pøesnou definici typù 
** naleznete v souboru c401.h.
**
** Pozor! Je tøeba správnì rozli¹ovat, kdy pou¾ít dereferenèní operátor *
** (typicky pøi modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem 
** (napø. pøi vyhledávání). V tomto pøíkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, pou¾ijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {
/*   -------
** Funkce provede poèáteèní inicializaci stromu pøed jeho prvním pou¾itím.
**
** Ovìøit, zda byl ji¾ strom pøedaný pøes RootPtr inicializován, nelze,
** proto¾e pøed první inicializací má ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Programátor vyu¾ívající ADT BVS tedy musí zajistit, aby inicializace
** byla volána pouze jednou, a to pøed vlastní prací s BVS. Provedení
** inicializace nad neprázdným stromem by toti¾ mohlo vést ke ztrátì pøístupu
** k dynamicky alokované pamìti (tzv. "memory leak").
**	
** V¹imnìte si, ¾e se v hlavièce objevuje typ ukazatel na ukazatel.	
** Proto je tøeba pøi pøiøazení pøes RootPtr pou¾ít dereferenèní operátor *.
** Ten bude pou¾it i ve funkcích BSTDelete, BSTInsert a BSTDispose.
**/
	
    *RootPtr = NULL;        // inicializace prazdneho stromu	
    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	
	
}	

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{
/*  ---------
** Funkce vyhledá uzel v BVS s klíèem K.
**
** Pokud je takový nalezen, vrací funkce hodnotu TRUE a v promìnné Content se
** vrací obsah pøíslu¹ného uzlu.´Pokud pøíslu¹ný uzel není nalezen, vrací funkce
** hodnotu FALSE a obsah promìnné Content není definován (nic do ní proto
** nepøiøazujte).
**
** Pøi vyhledávání v binárním stromu bychom typicky pou¾ili cyklus ukonèený
** testem dosa¾ení listu nebo nalezení uzlu s klíèem K. V tomto pøípadì ale
** problém øe¹te rekurzivním volání této funkce, pøièem¾ nedeklarujte ¾ádnou
** pomocnou funkci.
**/
    tBSTNodePtr NextPtr = RootPtr;
    if (NextPtr == NULL) // pokud neexistuje nasledovnik nenasli jsme
        return FALSE;
    else if (NextPtr->Key == K)	// pokud nasli jsme hledany prvek		   
    {
        *Content = NextPtr->BSTNodeCont;
        return TRUE;
    }
    else                    // prejdi na dalsi prvek
    {
        if (NextPtr->Key > K) // je mensi? jdi vlevo
            NextPtr = NextPtr->LPtr;
        else if (NextPtr->Key < K)  // je vetsi? jdi vpravo
            NextPtr = NextPtr->RPtr;
        return BSTSearch(NextPtr, K, Content); // proved se s dalsim a vrat zda jsi nasel
    }
    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	
	
} 


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{	
/*   ---------
** Vlo¾í do stromu RootPtr hodnotu Content s klíèem K.
**
** Pokud ji¾ uzel se zadaným klíèem ve stromu existuje, bude obsah uzlu
** s klíèem K nahrazen novou hodnotou. Pokud bude do stromu vlo¾en nový
** uzel, bude vlo¾en v¾dy jako list stromu.
**
** Funkci implementujte rekurzivnì. Nedeklarujte ¾ádnou pomocnou funkci.
**
** Rekurzivní implementace je ménì efektivní, proto¾e se pøi ka¾dém
** rekurzivním zanoøení ukládá na zásobník obsah uzlu (zde integer).
** Nerekurzivní varianta by v tomto pøípadì byla efektivnìj¹í jak z hlediska
** rychlosti, tak z hlediska pamì»ových nárokù. Zde jde ale o ¹kolní
** pøíklad, na kterém si chceme ukázat eleganci rekurzivního zápisu.
**/

    tBSTNodePtr NextPtr = *RootPtr, NewPtr;
		
    if ((*RootPtr) == NULL) // prazdny strom? vloz tam koren a zkonci
    {
        (*RootPtr) = malloc(sizeof(struct tBSTNode));
        (*RootPtr)->Key = K;
        (*RootPtr)->BSTNodeCont = Content;
        (*RootPtr)->LPtr = NULL;
        (*RootPtr)->RPtr = NULL;
        return;
    }
    else if (NextPtr->Key == K)	// aktualizij hodnoty pokud prvek jiz existuje
    {
        NextPtr->Key = K;
        NextPtr->BSTNodeCont = Content;
        return;
    }
    else
    {
        if (NextPtr->Key > K) // pracuj s levou stranou 
        {
            if (NextPtr->LPtr == NULL) // neexistuje levy, vytvor novy s danou hodnotou
            {
                if ((NewPtr = malloc(sizeof(struct tBSTNode))) != 0) // pokud se povedlo
                {
                    NewPtr->Key = K;
                    NewPtr->BSTNodeCont = Content;
                    NewPtr->LPtr = NULL;
                    NewPtr->RPtr = NULL;
                }
                NextPtr->LPtr = NewPtr; // pripoj novy list
                return;
            }
            else 
                NextPtr = NextPtr->LPtr; // jdi vpravo
        }
        else if (NextPtr->Key < K) // pracuj s pravou stanou
        {
            if (NextPtr->RPtr == NULL) // neexistuje pravy, vytvor novy s danou hodnotou

            {
                if ((NewPtr = malloc(sizeof(struct tBSTNode))) != 0) // pokud se povedlo
                {
                    NewPtr->Key = K;
                    NewPtr->BSTNodeCont = Content;
                    NewPtr->LPtr = NULL;
                    NewPtr->RPtr = NULL;
                }
                NextPtr->RPtr = NewPtr; // pripoj novy list
                return;
            }
            else 
                NextPtr = NextPtr->RPtr; // jdi vpravo
        }
    }
    BSTInsert(&NextPtr, K, Content); // proved se pro dalsi prvek
    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	
	
}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
/*   ------------------
** Pomocná funkce pro vyhledání, pøesun a uvolnìní nejpravìj¹ího uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do kterého bude pøesunuta hodnota
** nejpravìj¹ího uzlu v podstromu, který je urèen ukazatelem RootPtr.
** Pøedpokládá se, ¾e hodnota ukazatele RootPtr nebude NULL (zajistìte to
** testováním pøed volání této funkce). Tuto funkci implementujte rekurzivnì. 
**
** Tato pomocná funkce bude pou¾ita dále. Ne¾ ji zaènete implementovat,
** pøeètìte si komentáø k funkci BSTDelete(). 
**/
    tBSTNodePtr SavedPtr = NULL;
    if (*RootPtr == NULL) // je strom prazdny? pak nedelej
        return;

    if ((*RootPtr)->RPtr == NULL) // jsem nejvetsi prvek podstromu
    {
        // presun hodnoty z nejpravejsiho do prepisovaneho
        PtrReplaced->Key = (*RootPtr)->Key;
        PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
        SavedPtr = *RootPtr;
        *RootPtr = (*RootPtr)->LPtr; // zachovej levej podstrom nejpravejsiho   
        free(SavedPtr);
        return;
    }	
    else
    {
         ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr)); // proved se znova na pravem prvku
         return;
    }

    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	
	
}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{
/*   ---------
** Zru¹í uzel stromu, který obsahuje klíè K.
**
** Pokud uzel se zadaným klíèem neexistuje, nedìlá funkce nic. 
** Pokud má ru¹ený uzel jen jeden podstrom, pak jej zdìdí otec ru¹eného uzlu.
** Pokud má ru¹ený uzel oba podstromy, pak je ru¹ený uzel nahrazen nejpravìj¹ím
** uzlem levého podstromu. Pozor! Nejpravìj¹í uzel nemusí být listem.
**
** Tuto funkci implementujte rekurzivnì s vyu¾itím døíve deklarované
** pomocné funkce ReplaceByRightmost.
**/
    	
    tBSTNodePtr NextPtr = *RootPtr, SavedPtr = NULL;
    if (NextPtr->Key != K && NextPtr->LPtr == NULL && NextPtr->RPtr == NULL) // konec stromu, prvek neni prvek k smazani
        return;
    else
    {
        SavedPtr = NextPtr;
        if (NextPtr->Key > K) // jdi vlevo
            NextPtr = NextPtr->LPtr;
        else if (NextPtr->Key < K) // jdi vpravo
            NextPtr = NextPtr->RPtr;
        if (NextPtr != NULL) // dalsi prvek existuje
        {
            if (NextPtr->Key != K) // kdyz dalsi neni hledany prvek proved se znovu
                BSTDelete(&NextPtr, K);
            else
            {   // pokud existuje jenom jeden podstrom
                if (NextPtr->LPtr == NULL) 
                {
                    (SavedPtr->Key > K ? (SavedPtr->LPtr = NextPtr->RPtr) : (SavedPtr->RPtr = NextPtr->RPtr));
                free(NextPtr);
                }
                else if (NextPtr->RPtr == NULL)
                {
                    (SavedPtr->Key > K ? (SavedPtr->LPtr = NextPtr->LPtr) : (SavedPtr->RPtr = NextPtr->LPtr));
                
                free(NextPtr);
                }
                
                // pokud existuji oba podstromy
                else if (NextPtr->LPtr != NULL && NextPtr->RPtr != NULL)
                    ReplaceByRightmost(NextPtr, &(NextPtr->LPtr));
            }
        }
    }
    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	
} 

void BSTDispose (tBSTNodePtr *RootPtr) {	
/*   ----------
** Zru¹í celý binární vyhledávací strom a korektnì uvolní pamì».
**
** Po zru¹ení se bude BVS nacházet ve stejném stavu, jako se nacházel po
** inicializaci. Tuto funkci implementujte rekurzivnì bez deklarování pomocné
** funkce.
**/
	
    if (*RootPtr == NULL) // prazdny strom? nedelej nic
        return;
    else
    {
        if ((*RootPtr)->LPtr != NULL)       // pokud exituje levy podstrom
        {
            BSTDispose(&(*RootPtr)->LPtr);  // zavolej se a jdi doleva
            free((*RootPtr)->LPtr);         // uvolni levy
            (*RootPtr)->LPtr = NULL;        // smaz ukazatel na uvolneny
        }
        if ((*RootPtr)->RPtr != NULL)       // pokud existuje pravy podstrom
        {
            BSTDispose(&(*RootPtr)->RPtr);  // zavolej se a jdi doprava
            free((*RootPtr)->RPtr);         // uvolni pravy
            (*RootPtr)->RPtr = NULL;        // smaz ukazatel na uvoleny
        }
        free((*RootPtr));                   // uvolni koren
        (*RootPtr)= NULL;                   // uved do stavu po inicializaci
    }
    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	

}

/* konec c401.c */

