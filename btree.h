#include "bnode.h"

template<typename Type>class BTree{
	private:
		Bnode<Type> *m_root;
		const int maxsize;
		int sizes;
		void print1(Bnode<Type> *start,int n);
	public:
		
		BTree(int size):m_root(NULL),maxsize(size){sizes=0;}
		~BTree(){m_root->Destroy(m_root);}
		Triple<Type> Search(const Type item);//search后有否
		void insertkey(Bnode<Type>*insertnode,int n,Type item,Bnode<Type>*pnode);
		bool insert(const Type item);
		void Print();   
		//print the BTree
		Bnode<Type> *GetParent(const Type item); 
		void Premove(Bnode<Type> *root,int n);
		bool Remove(const Type item); 
	void Merge(Bnode<Type> *pleft, Bnode<Type> *pparent, Bnode<Type> *pright, int n);  
	void LeftAdjust(Bnode<Type> *pright,Bnode<Type>*pparent,int min,int n);	
	void RightAdjust(Bnode<Type> *pleft,Bnode<Type>*pparent,int min,int n);	

};

template<typename Type>void BTree<Type>::print1(Bnode<Type> *start,int n){
	if(start==NULL){
		return;
	}
	if(start->pointer[0]!=NULL)
	  {
		print1(start->pointer[0],n+1);
	  }else{
		for(int j=0;j<n;j++){
			cout<<" ";
		}
		cout<<"NULL"<<endl;
	}

	for(int i=0;i<=start->actuallsize;i++)
	{  
		for(int j=0;j<n;j++){
		cout<<" ";
	  }
		cout<<start->key[i]<<"---->"<<endl;

		if(start->pointer[i+1]!=NULL){
			print1(start->pointer[i+1],n+1);

		}else{
			for(int j=0;j<n;j++){
				cout<<" ";
			}
			cout<<"NULL"<<endl; 
		}
	}
}

template<typename Type>void BTree<Type>::Print()
{

	cout<<"vjfhvujfhvfdh"<<this->sizes<<endl;
	print1(m_root,0);

}
template <typename Type>void BTree<Type>::insertkey(Bnode<Type>*insertnode,int n,Type item,Bnode<Type>*pnode)
{  
	
	insertnode->actuallsize++;
	 this->sizes++;
 for(int i=insertnode->actuallsize;i>n;i--)
 {
	  insertnode->key[i]=insertnode->key[i-1];
      insertnode->pointer[i+1]=insertnode->pointer[i]; 

 
}
 insertnode->key[n]=item;
 insertnode->pointer[n+1]=pnode;

 if(insertnode->pointer[n+1]){

	 insertnode->pointer[n+1]->m_parent=insertnode;
   for(int i=0;i<=insertnode->pointer[n+1]->actuallsize;i++)
   {
	   if(insertnode->pointer[n+1]->pointer[i])
	   { insertnode->pointer[n+1]->pointer[i]->m_parent=insertnode->pointer[n+1];}

   }
 }

}

template<typename Type>	Triple<Type> BTree<Type>::Search(const Type item){

	 Bnode<Type> *p,*parent=NULL; Triple<Type> result;
	 p=m_root;
	 int i=0;
	 while(p)
	 {
	   i=-1;
	   while(item>p->key[++i]);	 
	   
	   if (p->key[i] == item){
		   result.m_pfind = p;
		   result.m_nfind = i;
		   result.m_ntag = 1;
		   cout << i << endl;
		   cout<<p<<endl;
		   return result;
	   }
       parent=p;

	   p=p->pointer[i];


        
	 }

	 result.m_pfind = parent;
	 result.m_nfind = i;
	 result.m_ntag = 0;
	 return result;


}

template<typename Type>Bnode<Type> *BTree<Type>::GetParent(const Type item){
    Bnode<Type>* parent;	Triple<Type> find;

	find=this->Search(item);
  parent=find.m_nfind;
  return parent;

}
template<typename Type>bool BTree<Type>::insert(const Type item){  

   
	if(m_root==NULL){
   
		m_root = new Bnode<Type>(maxsize);
        m_root->actuallsize = 1;
        m_root->key[1] = m_root->key[0];
        m_root->key[0] = item;
        m_root->pointer[0] = m_root->pointer[1] =NULL;
        return 1;




	}
	Bnode<Type>*parent;
	Bnode<Type>*newnode1;
	
	Bnode<Type> *newnode=NULL;
	
	Triple<Type> find;
     find=this->Search(item);//待插入的位置 
	 Bnode<Type>*p=find.m_pfind;
	 if(find.m_ntag){
		 cout<< "The item is exist!" << endl;
		 return 0;

	 }

     p=find.m_pfind;
	 int n=find.m_nfind;
	 Type key=item;
   
   while(1){

    if(p->actuallsize<p->maxsize-1)
	{
	
        this->insertkey(p,n,item,newnode);
       return 1;
	}

	int m=(p->actuallsize+1)/2;
	this->insertkey(p,n,key,newnode);
	newnode1 = new Bnode<Type>(this->maxsize);   //this place is the new node ,which provide the support for delete node, free space.

	 for (int i=m+1; i<=p->actuallsize; i++){      
		 newnode1->key[i-m-1] = p->key[i];
		 newnode1->pointer[i-m-1] = p->pointer[i];
		 p->key[i] = p->m_Infinity;
		 p->pointer[i] = NULL;
	 }
	 newnode1->actuallsize = p->actuallsize-m-1;
	 p->actuallsize = m;
	 
	 for (int i=0; i<=newnode1->actuallsize; i++)
	 {    //change the parent
		 if (newnode1->pointer[i]!=NULL){
			 newnode1->pointer[i]->m_parent = newnode1;
			 for (int j=0; j<=newnode1->pointer[i]->actuallsize; j++){
				 if (newnode1->pointer[i]->pointer[j]){
					 newnode1->pointer[i]->pointer[j]->m_parent = newnode1->pointer[i];
				       }
			 }
		 }
	   }

	for(int i=0;i<=p->actuallsize;i++)
	{
             if(p->pointer[i]!=NULL)
			 {
               p->pointer[i]->m_parent=p;
			   for(int j=0;j<=p->pointer[i]->actuallsize;j++)//少了个/?
			   {
				   if(p->pointer[i]->pointer[j]!=NULL){
                     p->pointer[i]->pointer[j]->m_parent= p->pointer[i];

				   }

			   }

			 }

	}
      
	key=p->key[m];
    newnode=newnode1;
    
  if(p->m_parent!=NULL)
  {
	  parent=p->m_parent;
	  parent->key[parent->actuallsize]=parent->m_Infinity;
	  n=-1;
	  while(key>parent->key[++n]);
	  newnode1->m_parent=p->m_parent;  
	 
      p=parent;
 

  }
  else{   //creat new root;

      m_root=new Bnode<Type>(this->maxsize);
	  m_root->actuallsize=1;
	  m_root->key[1]=m_root->key[0];
	  m_root->key[0]=key;
	  m_root->pointer[0]=p;
	  m_root->pointer[1]=newnode;
	  newnode1->m_parent=p->m_parent=m_root;
	  return 1;

      
        
   }
  
    }

  
	}

template<typename Type>	void BTree<Type>:: Premove(Bnode<Type> *root,int n){

   root->key[root->actuallsize]=root->m_Infinity;
   for(int i=n;i<root->actuallsize;i++)
   {
    root->key[i]=root->key[i+1];
	root->pointer[i+1]=root->pointer[i+2];

   }
  root->actuallsize--;

}

template <typename Type>void BTree<Type>::Merge(Bnode<Type> *pleft, Bnode<Type> *pparent, Bnode<Type> *pright, int n){


	pleft->key[pleft->actuallsize]=pparent->key[n];
	Bnode<Type>*ptemp;
	for (int i=0; i<=pright->actuallsize; i++){ //merge the two child tree and the parent
		pleft->key[pleft->actuallsize+i+1] = pright->key[i];
		pleft->pointer[pleft->actuallsize+i+1] = pright->pointer[i];
		ptemp = pleft->pointer[pleft->actuallsize+i+1];
		if (ptemp){         //change thd right child tree's parent
			ptemp->m_parent = pleft;
			for (int j=0; j<=ptemp->actuallsize; j++){
				if (ptemp->pointer[j]){
					ptemp->pointer[j]->m_parent = ptemp;
				}
			}
		}
	}

	pleft->actuallsize = pleft->actuallsize + pright->actuallsize + 1;
	delete pright;
	Premove(pparent, n);    





}

template<typename Type>void BTree<Type>::LeftAdjust(Bnode<Type> *pright,Bnode<Type>*pparent,int min,int n)
{
	 Bnode<Type>*pleft=pparent->pointer[n-1],*ptemp;  
	 if(pleft->actuallsize>min-1)
	 {
		 for(int i=pright->actuallsize;i>0;i--)
		 {
			 pright->key[i]=pright->key[i-1];
			 pright->pointer[i]=pright->pointer[i-1];

		 }
		 pright->key[0]=pparent->key[n-1];
		 pright->pointer[0]=pleft->pointer[pleft->actuallsize];
		 ptemp = pright->pointer[0];
		 if (ptemp){     //change the tree's parent which is moved
			 ptemp->m_parent = pright;
			 for (int i=0; i<ptemp->actuallsize; i++){
				 if (ptemp->pointer[i]){
					 ptemp->pointer[i]->m_parent = ptemp;
				 }
			 }
		 }
		 pparent->key[n-1] = pleft->key[pleft->actuallsize-1];
		 pleft->key[pleft->actuallsize] = pleft->m_Infinity;
		 pleft->actuallsize--;
		 pright->actuallsize++;
	 }
	 else {
		 Merge(pleft, pparent, pright, n-1);
	 }

     }
	 

template<typename Type>void BTree<Type>::RightAdjust(Bnode<Type> *pleft, Bnode<Type> *pparent, int min, int n)
{
	    Bnode<Type> *pright = pparent->pointer[1];  
		Bnode<Type>*ptemp; //1-->n,
	    if(pright && pright->actuallsize > min-1){
		pleft->key[pleft->actuallsize] = pparent->key[0]; //0-->n-1
		pparent->key[n] = pright->key[0];  //change le
		pleft->pointer[pleft->actuallsize+1] = pright->pointer[0];
		ptemp = pleft->pointer[pleft->actuallsize+1];
		if (ptemp){         //change the tree's parent which is moved
			ptemp->m_parent = pleft;
			for (int i=0; i<ptemp->actuallsize; i++){
				if (ptemp->pointer[i]){
					ptemp->pointer[i]->m_parent = ptemp;
				}
			}
		}
	//	pright->pointer[0] = pright->pointer[1];//大问题????
		pleft->actuallsize++;
		Premove(pright,n);
	}
	else {
		Merge(pleft, pparent, pright, 0);  //0------>n,感觉有问题,与上面的不对称阿
	}


}

template <typename Type>bool BTree<Type>::Remove(const Type item){

	Triple<Type> result=this->Search(item);
	if(result.m_ntag){
		return 0;
	}
	Bnode<Type> *pdel,*pparent,*pmin;
	int n=result.m_nfind;
	pdel=result.m_pfind;
	if (pdel->pointer[n+1] != NULL){  //change into delete leafnode
		pmin = pdel->pointer[n+1];
		pparent = pdel;
		while (pmin != NULL){
			pparent = pmin;
			pmin = pmin->pointer[0]; 
		}
		pdel->key[n] = pparent->key[0];
		pdel = pparent;
		n = 0;
	}

	Premove(pdel, n); //delete the node

	 int min = (this->maxsize + 1) / 2;
	while (pdel->actuallsize< min-1){  //if it is not a BTree, then adjust
		n = 0;
		pparent = pdel->m_parent;
		if (NULL == pparent) 
		{
			return 1;
		}
		while (n<= pparent->actuallsize&& pparent->pointer[n]!=pdel){
			n++;
		}
		if (!n){
			RightAdjust(pdel, pparent, min, n); //adjust with the parent and the right child tree
		}
		else {
			LeftAdjust(pdel, pparent, min, n); //adjust with the parent and the left child tree
		}
		pdel = pparent;
		if (pdel == this->m_root){
			break;
		}
	}
	if (!m_root->actuallsize){         //the root is merged
		pdel = m_root->pointer[0];
		delete m_root;
		m_root = pdel;
		m_root->m_parent = NULL;
		for (int i=0; i<m_root->actuallsize; i++){
			if (m_root->pointer[i]){
				m_root->pointer[i]->m_parent = m_root;
			}
		}
	}
	return 1;
}