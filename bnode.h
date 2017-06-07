
template<typename Type> class BTree;
template<typename Type>class Bnode{
 private:
	 int actuallsize;
	 int maxsize;
	 Bnode<Type> *m_parent;
	 Bnode<Type> **pointer;
     Type *key;
	 
	 static const Type m_Infinity = 10000;
 public:
	    friend BTree<Type>;
		Bnode(int size0):actuallsize(0),maxsize(size0),key(NULL),pointer(NULL),m_parent(NULL){
			pointer=new Bnode<Type>*[size0+1];
			key=new Type[size0+1];
			
			for(int i=0;i<size0;i++){
				pointer[i]=NULL;   //之前的经验，，指针数组，指针有所指向，一般初始化为NULL，否则会导致野指针，类似的如之前介绍的图指针一样
			     key[i]=m_Infinity;
		       }
		}
		~Bnode(){
			//delete []pointer; //下面的两行与此行的区别是甚么哦
			if(maxsize){
			for(int i=0;i<maxsize;i++)
				pointer[i]=NULL;  
			delete []key;
		
			
		}
		}
		void Destroy( Bnode<Type>*p);
		bool isfull();
		Type GetKey(int i);
};


template<typename Type> void Bnode<Type>::Destroy(Bnode<Type> *proot){
	
	
	if (NULL == proot){
        return;
    }
	
	for(int i=0;i<proot->actuallsize;i++)
		Destroy(proot->pointer[i]);
	
    	delete(proot);
	
}
template<typename Type> bool Bnode<Type>::isfull(){
	return actuallsize==maxsize;
	
}
template<typename Type> Type Bnode<Type>::GetKey(int i){
	
	if(this){
		
		return key[i];
	}
	return -1;
}





template<typename Type> struct Triple{
    Bnode<Type> *m_pfind;
    int m_nfind;
    bool m_ntag;
};
