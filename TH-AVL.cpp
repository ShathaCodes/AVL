#include <iostream>
#include<stdlib.h>
using namespace std;

typedef struct nd
{int val;
struct nd* fg;
struct nd* fd;
int balance;
}Noeud;
typedef Noeud* AVL;


AVL * initialiser_table (int m)
{
	AVL * TH;
	AVL temp;
	if (( TH = (AVL*)malloc(m * sizeof( AVL)))==NULL)
	cout<< "erreur"<<endl ;
	for ( int i = 0; i<m; i++){
			//TH[i] = (AVL)malloc(sizeof( AVL*)) ;
			temp=(AVL)malloc(sizeof(Noeud));
			temp->val =i;
			temp->fg= NULL;
			temp->fd=NULL;
			TH[i]=temp;
			cout << "yay  " << TH[i]->val<<endl;
	}
	return TH;

}






int h(int c){
	return c%13;
}

AVL rotationDroite(AVL x){
	AVL y = x->fg;
	AVL temp = y->fd;
	y->fd = x;
	x->fg = temp;
	int bx = x->balance;
	x->balance = x->balance -1 - max(0,y->balance);
	if(x->balance >=0)
	y->balance--;
	else
	y->balance = bx -2 + min(0,y->balance);
	return y;
}
AVL rotationGauche(AVL x){
	AVL y = x->fd;
	AVL temp = y->fg;
	y->fg = x;
	x->fd = temp;
	int bx = x->balance;
	x->balance = x->balance +1 - min(0,y->balance);
	if(x->balance <0)
	y->balance++;
	else
	y->balance = bx +2 + max(0,y->balance);
	return y;
}

AVL rotationDoubleDG(AVL x){
	x->fd = rotationDroite(x->fd);
	return rotationGauche(x);
}
AVL rotationDoubleGD(AVL x){
	x->fg = rotationGauche(x->fg);
	return rotationDroite(x);
}
AVL reequilibre(AVL x){
	if(x->balance > 0){
		if(x->fg->balance >0)
			return rotationDroite(x);
		else
			return rotationDoubleGD(x);
	}
	else
	{
		if(x->fd->balance <0)
			return rotationGauche(x);
		else
			return rotationDoubleDG(x);
	}
}
AVL insert_arbre(AVL a, AVL x, bool * modif){
	if (a == NULL ){
		*modif = true;
		return x;
	}
	if ( x->val > a->val){
		a->fd=insert_arbre(a->fd,x,modif);
		if (*modif)
		a->balance --;
	}
	else{
		a->fg=insert_arbre(a->fg,x,modif);
		if (*modif)
		a->balance ++;
	}
	if ( abs(a->balance) > 1){
		a=reequilibre(a);
	}
	if(a->balance ==0)
		*modif=false;
	return a;
}

AVL heritier(AVL x, bool * modif,AVL * h){
	if(x->fd == NULL){
		*h= x;
		*modif = true;
		return x->fg;
	}
	x->fd = heritier(x->fd,modif,h);
	if(*modif)
		x->balance ++;
	if ( x->balance > 1 )
		x=reequilibre(x);
	if (x->balance !=0)
	*modif = false;
	return x;


}
AVL supprimer(AVL a, int v , bool * modif){
	if (a==NULL)
	return NULL;
	if ( v > a->val){
		a->fd=supprimer(a->fd,v,modif);
		if (*modif)
		a->balance ++;
	}
	else if( v < a->val){
		a->fg=supprimer(a->fg,v,modif);
		if (*modif)
		a->balance --;
	}
	else{
		if(a->fg == NULL){
			*modif = true;
			return a->fd;
		}
		else if(a->fd == NULL){
			*modif = true;
			return a->fg;
		}
		else{
			AVL h;
			a->fg = heritier(a->fg,modif,&h);
			a->val = h->val;
			if(*modif)
			a->balance --;
		}
	}
	if ( a->balance > 1 )
		a=reequilibre(a);
	if (a->balance !=0)
		*modif = false;
	return a;
}

bool recherche_arbre(AVL x, int val){
	if ( x == NULL)
		return false;
	if( val == x->val)
	return true;
	if( val > x->val)
	return recherche_arbre(x->fd,val);
	return recherche_arbre(x->fg,val);
}
void affichage_arbre(AVL x){
	if (x!= NULL){
		affichage_arbre(x->fg);
		cout << x->val << endl;
		affichage_arbre(x->fd);
	}

}


AVL * insert (AVL * TH, int m, int cle){
	int k = h(cle);
	AVL a = TH[k];
	bool modif;
	AVL x = (Noeud*)malloc( sizeof( Noeud)) ;
	x->val=cle;
	x->fg=NULL;
	x->fd=NULL;
	a = insert_arbre(a,x,&modif);
	TH[k]=a;
	return TH;
}
void affichage (AVL * TH, int m){
	for (int i=0; i<m;i++){
		affichage_arbre(TH[i]);
	}
}
bool rechercher(AVL * TH, int m, int cle) {
	int k = h(cle);
	AVL x= TH[k];
	return (recherche_arbre(x,cle));
}


int main(){

	AVL* TH;
	int m=3;
	TH= initialiser_table ( m);
	affichage(TH,m);
	TH = insert(TH,m,26);
	cout << "yayyyyyy";
	TH = insert(TH,m,13);


	cout << "yayyyyyy";
	return 0;
}
