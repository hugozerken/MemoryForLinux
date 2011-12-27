#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "Page.h"
#include "PageControl.h"
#include <vector>
//class CPage;
//class CPageControl;

class CMemory{
  public:
     CMemory();
     void initialize (const int nTotal_pf);
     void FIFO (const int nTotal_pf);
     void LRU (const int nTotal_pf);
     void NUR (const int nTotal_pf);
     void OPT (const int nTotal_pf);
  private:
     vector<CPage> _vDiscPages;
     vector<CPageControl> _vMemoryPages;
     CPageControl *_pFreepf_head, *_pBusypf_head, *_pBusypf_tail;
     vector<int> _vMain, _vPage, _vOffset;
     int _nDiseffect;

};

CMemory::CMemory(): _vDiscPages(TOTAL_VP),
                      _vMemoryPages(TOTAL_VP),
                      _vMain(TOTAL_INSTRUCTION),
                      _vPage(TOTAL_INSTRUCTION),
                      _vOffset(TOTAL_INSTRUCTION) {
     int s, i, nRand;
     srand (getpid () *10);
     nRand=rand () %32767;

     S= (float) 319*nRand/32767+1;
     for (i=0; i<TOTAL_INSTRUCTION; i+=4)     {
           _vMain[i]=S;
           _vMain[i+1]=_vMain[i]+1;
           nRand=rand () %32767;
            _vMain[i+2]=(float)_vMain[i]*nRand/32767;
            _vMain[i+3]=_vMain[2]+1;
            nRand=rand () %32767;
            S= (float) nRand *(318-_vMain[i+2])/32767+_vMain[i+2]+1;
}
  for (i=0; i<TOTAL_INSTRUCTION; i++)           {
         _vPage[i]=_vMain[i]/10;
         _vOffset[i]=_vMain[i]%10;
         _vPage[i]%=32;
  }

}
void CMemory::initialize (const int nTatal_pf)          {
       int ix;
       _nDiseffect=0;
       for (ix=0; ix<_vDiscPages.size(); ix++)               {
              _vDiscPages[ix].m_nPageNumber=ix;
              _vDiscPages[ix].m_nPageFaceNumber=INVALLD;
              _vDiscPages[ix].m_nCounter=0;
              _vDiscPages[ix].m_nTime=-1;
       }
       for (ix=1; ix<nTOTAL_pf; ix++)                       {
              _vMemoryPages[ix-1].m_pNext=&_vMemoryPages[ix];
              _vMemoryPages[ix-1].m_nPageFaceNumber=ix-1;
       }
        _vMemoryPages[nTotal_pf-1].m_pNext=NULL;
        _vMemoryPages[nTotal_pf-1].m_nPageFaceNumber=nTotal_pf-1;
        _pFreepf_head=&_vMemoryPages[0];
}

void CMemory::FIFO (const int nTotal_pf)                {
       int i;
       CPageControl *p;
       initialize (nTotal_pf);
       _pBusypf_head=_pBusypf_tail=NULL;
       for (i=0; i<TOTAL_INSTRUCTION; i++)         {
          if(_vDiscPages[_vPage[i]].m_nPageFaceNumber==INVALID)    {
          _nDiscffect+=1;
          if(_pFreepf_head==NULL)    //ÎÞ¿ÕÏÐÒ³Ãæ
          {
              p=_pBusypf_head->m_pNext;
             _vDiscPages[_pBusypf_head->m_nPageNumber].m_nPageFaceNumber=INVALID;
             _pFreepf_head=_pBusypf_head;
             _pFreepf_head->m_pNext=NULL;
             _pBusypf_head=p;
           }
             p=_pFreepf_head->m_pNext;
             _pFreepf_head->m_pNext=NULL;
             _pBusypf_head->m_PageNumber=_pFreepf_head->m_nPageFaceNumber;
            if (_pBusypf_tail==NULL)
            _pBusypf_head=_pBusypf_tail=_pFreepf_head;
            else               {

             _pBusypf_tail->m_pNext=pFreepf_head;
             _pBusypf_tail=pFreepf_head;
             }
        }
      cout<<"FIFO: "<<1-(float)_nDiseffect/320;
}

void CMemory::LRU(const int nTotal_pf)            {
    int i, j, nMin, minj, nPresentTime(0);
    initialize(nTotal_pf);
    for(i=0; i<TOTAL_INSTRUCTION; i++)       {
            if(_vDiscPages[_vPage[i]].m_nPageFaceNumber==INVALID)    {
            _nDiseffect++;
            if(_pFreepf_head==NULL)                                {
                  nMin=32767;
                  for(j=0; j<TOTAL_VP; j++)
                if(nMin>_vDiscPages[j].m_nTime&&_vDiscPages[j].m_nPageFaceNumber!=INVALID)
                {
                      nMin=_vDiscPages[j].m_nTime;
                      minj=j;
                 }
               _pFreepf_head=&_vMemoryPages[ vDiscPages[minj].m_nPageFaceNumber];
               _vDiscPages[minj].m_nPageFaceNumber=INVALID;
               _vDiscPages[minj].m_nTime=-1;
               _pFreepf_head->m_pNext=NULL;
             }
           _vDiscPages[_vPage[i]].m_nPageFaceNumber= _pFreepf_head->m_nPageFaceNumber;
           _vDiscPages[_vPage[i]].m_nTime=nPresentTime;
           _pFreepf_head= _pFreepf_head->m_pNext;
       }
         else
        _vDiscPages[_vPage[i]].m_nTime=nPresentTime;

          nPresentTime++;
        }
      cout<<"LRU: "1-(float)_nDiseffect/320;
}

void CMenory::NUR(const int nTotal_pf)
{
    int i,j,nDiscPage,nOld_DisPage;
    bool bCont_flag;
    initiaze(nTotal_pf);
    for(i = 0;i < TOTAL_INSTRUTION;i++)
    {
        if(_vDiscPages[_vPage[i]].m_nPageFaceNumber == INVALID)
        {
            _nDiseffect++;
            if(_pFreepf_head == NULL)
            {
                bCont_flag=true;
                nOld_DiscPage = nDiscPage;
                while(bCont_flag)
                {
                    if(_vDiscPages[nDiscPage].m_nCounter == 0 && _vDiscPages[nDiscPage].m_nPageFaceNumber != INVALID)\
                    bCont_flag = false;
                    else{
                        nDiscPage++;
                        if(nDiscPage == TOTAL_VP)nDiscPage = 0;
                        if(nDiscPage == nOld_DisPage)
                        for(j=0;j < TOTAL_VP;j++)
                        _vDiscPages[j].m_nCounter = 0;
                    }
                }
                _pFreepf_head = &_vMemoryPages[_vDiscPages[nDiscPage].m_nPageFaceNumber];
                _vDiscPages[nDiscPage].m_nPageFaceNumber = INVALID;
                _pFreepf_head -> m_pNext = NULL;
            }
            _vDiscPages[_vPage[i]].m_nPageFaceNumber = _pFreepf_head -> m_nPageFaceNUmber;
            _pFreepf_head = _pFreepf_head = m_pNext = NULL;
        }

    else
    _vDiscPages[_vPage[i]].m_nCounter = 1;
    if(i%CLEAR_PERIOD == 0)
    for(j = 0; j < TOTAL_VP;j++)
    _vDiscPages[j].m_nCounter = 0;

    }
    cout<<"NUR:"<<1-(float)_nDiseffect/320;
}

void CMemory::OPT(const int nTotal_pf)
{
    int i,j,max,maxpage,nDistance,vDistance[TOTAL_VP];
    initialize(nTotal_pf);
    for(i = 0; i <TOTAL_INSTRUCTION;i++)
    {
        if(_vDiscPages[_vPage[i]].m_nPageFaceNumber == INVALID)
        {
            _nDiseffect++;
            if(_pFreepf_head == NULL)
            {
                for(j = 0;j < TOTAL_VP;j++)
                {
                    if((_vDiscPages[j].m_nPageFaceNumber != INVALID) && (vDistance[_vPage[j]] == 32767))
                    vDistance[_vPage[j]] = nDistance;
                    nDistance++;
                }
                max = -1;
                for(j = 0;j < TOTAL_VP;j++)
                if(max < vDistance[j])
                {
                    max = vDistance[j];
                    maxpage = j;
                }
                _pFreepf_head = &_vMemoryPages[_vDiscPages[maxpage].m_nPageFaceNumber];
                _pFreepf_head->m_pNext = NULL;
                _vDiscPages[maxpage].m_nPageFaceNumber = INVALID;
            }
            _vDiscPages[_vPage[i]].m_nPageFaceNumber = _pFreepf_head->m_nPageFaceNumber;
            _pFreepf_head = _pFreepf_head->m_pNext;
        }
    }
    cout<<"OPT:"<<1-(float)_nDiseffect/320;
}

#endif // MEMORY_H_INCLUDED
