
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
	
    *RootPtr = NULL;	
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
    if (NextPtr == NULL)
        return FALSE;
    else if (NextPtr->Key == K)							   
    {
        *Content = NextPtr->BSTNodeCont;
        return TRUE;
    }
    else
    {
        if (NextPtr->Key < K)
            NextPtr = NextPtr->LPtr;
        else if (NextPtr->Key > K)
            NextPtr = NextPtr->RPtr;
        return BSTSearch(NextPtr, K, Content);
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
		
    if ((*RootPtr) == NULL)
    {
        (*RootPtr) = malloc(sizeof(struct tBSTNode));
        (*RootPtr)->Key = K;
        (*RootPtr)->BSTNodeCont = Content;
        (*RootPtr)->LPtr = NULL;
        (*RootPtr)->RPtr = NULL;
        return;
    }
    else if (NextPtr->Key == K)							   
    {
        NextPtr->Key = K;
        NextPtr->BSTNodeCont = Content;
        return;
    }
    else
    {
        if (NextPtr->Key < K)
        {
            if (NextPtr->LPtr == NULL)
            {
                if ((NewPtr = malloc(sizeof(struct tBSTNode))) != 0)
                {
                    NewPtr->Key = K;
                    NewPtr->BSTNodeCont = Content;
                    NewPtr->LPtr = NULL;
                    NewPtr->RPtr = NULL;
                }
                NextPtr->LPtr = NewPtr;
                return;
            }
            else 
                NextPtr = NextPtr->LPtr;
        }
        else if (NextPtr->Key > K)
        {
            if (NextPtr->RPtr == NULL)
            {
                if ((NewPtr = malloc(sizeof(struct tBSTNode))) != 0)
                {
                    NewPtr->Key = K;
                    NewPtr->BSTNodeCont = Content;
                    NewPtr->LPtr = NULL;
                    NewPtr->RPtr = NULL;
                }
                NextPtr->RPtr = NewPtr; 
                return;
            }
            else 
                NextPtr = NextPtr->RPtr;
        }
    }
    BSTInsert(&NextPtr, K, Content); 
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
    if (*RootPtr == NULL)
        return;
    if ((*RootPtr)->RPtr == NULL)
    {
        PtrReplaced->Key = (*RootPtr)->Key;
        PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
        PtrReplaced->LPtr = (*RootPtr)->LPtr;
        PtrReplaced->RPtr = (*RootPtr)->RPtr;
        return;
    }	
    else
         ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr));
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
    if (NextPtr->Key != K && NextPtr->LPtr == NULL && NextPtr->RPtr == NULL)
        return;
    else
    {
        SavedPtr = NextPtr;
        if (NextPtr->Key < K)
            NextPtr = NextPtr->LPtr;
        else if (NextPtr->Key > K)
            NextPtr = NextPtr->RPtr;
        if (NextPtr != NULL)
        {
            if (NextPtr->Key != K) 
                BSTDelete(&NextPtr, K);
            else
            {
                if (NextPtr->LPtr == NULL)
                    (SavedPtr->Key < K ? (SavedPtr->LPtr = NextPtr->RPtr) : (SavedPtr->RPtr = NextPtr->RPtr));
                else if (NextPtr->RPtr == NULL)
                    (SavedPtr->Key < K ? (SavedPtr->LPtr = NextPtr->LPtr) : (SavedPtr->RPtr = NextPtr->LPtr));
                else 
                    ReplaceByRightmost(SavedPtr, &(NextPtr->LPtr));
                free(NextPtr);
                return;
            }
            return;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /* if (NextPtr->Key != K && NextPtr->LPtr == NULL && NextPtr->RPtr == NULL)	
        return;
    else if (NextPtr->Key < K)
    {
        if (NextPtr->LPtr->Key != K)
            NextPtr = NextPtr->LPtr;
        else
        {
            SavedPtr = NextPtr->LPtr;
            if (NextPtr->LPtr->LPtr == NULL)
                NextPtr->LPtr = NextPtr->LPtr->RPtr;
            else if (NextPtr->LPtr->RPtr == NULL)
                NextPtr->LPtr = NextPtr->LPtr->LPtr;
            else
            {
                ReplaceByRightmost(NextPtr, &(NextPtr->LPtr));
                free(SavedPtr);
                return;
            }
        }
        BSTDelete(&NextPtr, K);
    }
    else if (NextPtr->Key > K)
    {
        if (NextPtr->RPtr->Key != K)
            NextPtr = NextPtr->RPtr;
        else
        {   
            SavedPtr = NextPtr->RPtr;
            if (NextPtr->RPtr->LPtr == NULL)
                NextPtr->RPtr = NextPtr->RPtr->LPtr;
            else if (NextPtr->RPtr->RPtr == NULL)
                NextPtr->RPtr = NextPtr->RPtr->RPtr;
            else
            {
                ReplaceByRightmost(NextPtr, &(NextPtr->LPtr));
                free(SavedPtr);
                return;
            }
        }
        BSTDelete(&NextPtr, K);
    }
    else
    {
        free(NextPtr);
        return;
    }

    free(SavedPtr);
    return;
    */
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
	
    if (*RootPtr == NULL)
        return;
    if ((*RootPtr)->LPtr != NULL)
        BSTDispose(&(*RootPtr)->LPtr);
    if ((*RootPtr)->RPtr != NULL)
        BSTDispose(&(*RootPtr)->RPtr);
    free(RootPtr);

    solved = TRUE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */	

}

/* konec c401.c */

