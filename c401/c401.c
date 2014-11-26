
/* c401.c: **********************************************************}
{* T�ma: Rekurzivn� implementace operac� nad BVS
**                                         Vytvo�il: Petr P�ikryl, listopad 1994
**                                         �pravy: Andrea N�mcov�, prosinec 1995
**                                                      Petr P�ikryl, duben 1996
**                                                   Petr P�ikryl, listopad 1997
**                                  P�evod do jazyka C: Martin Tu�ek, ��jen 2005
**                                         �pravy: Bohuslav K�ena, listopad 2009
**                                         �pravy: Karel Masa��k, ��jen 2013
**                                         �pravy: Radek Hranick�, ��jen 2014
**
** Implementujte rekurzivn�m zp�sobem operace nad bin�rn�m vyhled�vac�m
** stromem (BVS; v angli�tin� BST - Binary Search Tree).
**
** Kl��em uzlu stromu je jeden znak (obecn� j�m m��e b�t cokoliv, podle
** �eho se vyhled�v�). U�ite�n�m (vyhled�van�m) obsahem je zde integer.
** Uzly s men��m kl��em le�� vlevo, uzly s v�t��m kl��em le�� ve stromu
** vpravo. Vyu�ijte dynamick�ho p�id�lov�n� pam�ti.
** Rekurzivn�m zp�sobem implementujte n�sleduj�c� funkce:
**
**   BSTInit ...... inicializace vyhled�vac�ho stromu
**   BSTSearch .... vyhled�v�n� hodnoty uzlu zadan�ho kl��em
**   BSTInsert .... vkl�d�n� nov� hodnoty
**   BSTDelete .... zru�en� uzlu se zadan�m kl��em
**   BSTDispose ... zru�en� cel�ho stromu
**
** ADT BVS je reprezentov�n ko�enov�m ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje kl�� (typu char), podle
** kter�ho se ve stromu vyhled�v�, vlastn� obsah uzlu (pro jednoduchost
** typu int) a ukazatel na lev� a prav� podstrom (LPtr a RPtr). P�esnou definici typ� 
** naleznete v souboru c401.h.
**
** Pozor! Je t�eba spr�vn� rozli�ovat, kdy pou��t dereferen�n� oper�tor *
** (typicky p�i modifikaci) a kdy budeme pracovat pouze se samotn�m ukazatelem 
** (nap�. p�i vyhled�v�n�). V tomto p��kladu v�m napov� prototypy funkc�.
** Pokud pracujeme s ukazatelem na ukazatel, pou�ijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) {
/*   -------
** Funkce provede po��te�n� inicializaci stromu p�ed jeho prvn�m pou�it�m.
**
** Ov��it, zda byl ji� strom p�edan� p�es RootPtr inicializov�n, nelze,
** proto�e p�ed prvn� inicializac� m� ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Program�tor vyu��vaj�c� ADT BVS tedy mus� zajistit, aby inicializace
** byla vol�na pouze jednou, a to p�ed vlastn� prac� s BVS. Proveden�
** inicializace nad nepr�zdn�m stromem by toti� mohlo v�st ke ztr�t� p��stupu
** k dynamicky alokovan� pam�ti (tzv. "memory leak").
**	
** V�imn�te si, �e se v hlavi�ce objevuje typ ukazatel na ukazatel.	
** Proto je t�eba p�i p�i�azen� p�es RootPtr pou��t dereferen�n� oper�tor *.
** Ten bude pou�it i ve funkc�ch BSTDelete, BSTInsert a BSTDispose.
**/
	
    *RootPtr = NULL;        // inicializace prazdneho stromu	
    solved = TRUE;		  /* V p��pad� �e�en� sma�te tento ��dek! */	
	
}	

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content)	{
/*  ---------
** Funkce vyhled� uzel v BVS s kl��em K.
**
** Pokud je takov� nalezen, vrac� funkce hodnotu TRUE a v prom�nn� Content se
** vrac� obsah p��slu�n�ho uzlu.�Pokud p��slu�n� uzel nen� nalezen, vrac� funkce
** hodnotu FALSE a obsah prom�nn� Content nen� definov�n (nic do n� proto
** nep�i�azujte).
**
** P�i vyhled�v�n� v bin�rn�m stromu bychom typicky pou�ili cyklus ukon�en�
** testem dosa�en� listu nebo nalezen� uzlu s kl��em K. V tomto p��pad� ale
** probl�m �e�te rekurzivn�m vol�n� t�to funkce, p�i�em� nedeklarujte ��dnou
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
    solved = TRUE;		  /* V p��pad� �e�en� sma�te tento ��dek! */	
	
} 


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content)	{	
/*   ---------
** Vlo�� do stromu RootPtr hodnotu Content s kl��em K.
**
** Pokud ji� uzel se zadan�m kl��em ve stromu existuje, bude obsah uzlu
** s kl��em K nahrazen novou hodnotou. Pokud bude do stromu vlo�en nov�
** uzel, bude vlo�en v�dy jako list stromu.
**
** Funkci implementujte rekurzivn�. Nedeklarujte ��dnou pomocnou funkci.
**
** Rekurzivn� implementace je m�n� efektivn�, proto�e se p�i ka�d�m
** rekurzivn�m zano�en� ukl�d� na z�sobn�k obsah uzlu (zde integer).
** Nerekurzivn� varianta by v tomto p��pad� byla efektivn�j�� jak z hlediska
** rychlosti, tak z hlediska pam�ov�ch n�rok�. Zde jde ale o �koln�
** p��klad, na kter�m si chceme uk�zat eleganci rekurzivn�ho z�pisu.
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
    solved = TRUE;		  /* V p��pad� �e�en� sma�te tento ��dek! */	
	
}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
/*   ------------------
** Pomocn� funkce pro vyhled�n�, p�esun a uvoln�n� nejprav�j��ho uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do kter�ho bude p�esunuta hodnota
** nejprav�j��ho uzlu v podstromu, kter� je ur�en ukazatelem RootPtr.
** P�edpokl�d� se, �e hodnota ukazatele RootPtr nebude NULL (zajist�te to
** testov�n�m p�ed vol�n� t�to funkce). Tuto funkci implementujte rekurzivn�. 
**
** Tato pomocn� funkce bude pou�ita d�le. Ne� ji za�nete implementovat,
** p�e�t�te si koment�� k funkci BSTDelete(). 
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

    solved = TRUE;		  /* V p��pad� �e�en� sma�te tento ��dek! */	
	
}

void BSTDelete (tBSTNodePtr *RootPtr, char K) 		{
/*   ---------
** Zru�� uzel stromu, kter� obsahuje kl�� K.
**
** Pokud uzel se zadan�m kl��em neexistuje, ned�l� funkce nic. 
** Pokud m� ru�en� uzel jen jeden podstrom, pak jej zd�d� otec ru�en�ho uzlu.
** Pokud m� ru�en� uzel oba podstromy, pak je ru�en� uzel nahrazen nejprav�j��m
** uzlem lev�ho podstromu. Pozor! Nejprav�j�� uzel nemus� b�t listem.
**
** Tuto funkci implementujte rekurzivn� s vyu�it�m d��ve deklarovan�
** pomocn� funkce ReplaceByRightmost.
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
    solved = TRUE;		  /* V p��pad� �e�en� sma�te tento ��dek! */	
} 

void BSTDispose (tBSTNodePtr *RootPtr) {	
/*   ----------
** Zru�� cel� bin�rn� vyhled�vac� strom a korektn� uvoln� pam�.
**
** Po zru�en� se bude BVS nach�zet ve stejn�m stavu, jako se nach�zel po
** inicializaci. Tuto funkci implementujte rekurzivn� bez deklarov�n� pomocn�
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
    solved = TRUE;		  /* V p��pad� �e�en� sma�te tento ��dek! */	

}

/* konec c401.c */

