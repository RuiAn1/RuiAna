// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME ShiYan_TrackAnalysisDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "GetDeviation.h"
#include "TrackDeviation.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *larlitecLcLTrackDeviation_Dictionary();
   static void larlitecLcLTrackDeviation_TClassManip(TClass*);
   static void *new_larlitecLcLTrackDeviation(void *p = 0);
   static void *newArray_larlitecLcLTrackDeviation(Long_t size, void *p);
   static void delete_larlitecLcLTrackDeviation(void *p);
   static void deleteArray_larlitecLcLTrackDeviation(void *p);
   static void destruct_larlitecLcLTrackDeviation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::larlite::TrackDeviation*)
   {
      ::larlite::TrackDeviation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::larlite::TrackDeviation));
      static ::ROOT::TGenericClassInfo 
         instance("larlite::TrackDeviation", "TrackDeviation.h", 48,
                  typeid(::larlite::TrackDeviation), DefineBehavior(ptr, ptr),
                  &larlitecLcLTrackDeviation_Dictionary, isa_proxy, 4,
                  sizeof(::larlite::TrackDeviation) );
      instance.SetNew(&new_larlitecLcLTrackDeviation);
      instance.SetNewArray(&newArray_larlitecLcLTrackDeviation);
      instance.SetDelete(&delete_larlitecLcLTrackDeviation);
      instance.SetDeleteArray(&deleteArray_larlitecLcLTrackDeviation);
      instance.SetDestructor(&destruct_larlitecLcLTrackDeviation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::larlite::TrackDeviation*)
   {
      return GenerateInitInstanceLocal((::larlite::TrackDeviation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::larlite::TrackDeviation*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *larlitecLcLTrackDeviation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::larlite::TrackDeviation*)0x0)->GetClass();
      larlitecLcLTrackDeviation_TClassManip(theClass);
   return theClass;
   }

   static void larlitecLcLTrackDeviation_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *larlitecLcLGetDeviation_Dictionary();
   static void larlitecLcLGetDeviation_TClassManip(TClass*);
   static void *new_larlitecLcLGetDeviation(void *p = 0);
   static void *newArray_larlitecLcLGetDeviation(Long_t size, void *p);
   static void delete_larlitecLcLGetDeviation(void *p);
   static void deleteArray_larlitecLcLGetDeviation(void *p);
   static void destruct_larlitecLcLGetDeviation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::larlite::GetDeviation*)
   {
      ::larlite::GetDeviation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::larlite::GetDeviation));
      static ::ROOT::TGenericClassInfo 
         instance("larlite::GetDeviation", "GetDeviation.h", 26,
                  typeid(::larlite::GetDeviation), DefineBehavior(ptr, ptr),
                  &larlitecLcLGetDeviation_Dictionary, isa_proxy, 4,
                  sizeof(::larlite::GetDeviation) );
      instance.SetNew(&new_larlitecLcLGetDeviation);
      instance.SetNewArray(&newArray_larlitecLcLGetDeviation);
      instance.SetDelete(&delete_larlitecLcLGetDeviation);
      instance.SetDeleteArray(&deleteArray_larlitecLcLGetDeviation);
      instance.SetDestructor(&destruct_larlitecLcLGetDeviation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::larlite::GetDeviation*)
   {
      return GenerateInitInstanceLocal((::larlite::GetDeviation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::larlite::GetDeviation*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *larlitecLcLGetDeviation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::larlite::GetDeviation*)0x0)->GetClass();
      larlitecLcLGetDeviation_TClassManip(theClass);
   return theClass;
   }

   static void larlitecLcLGetDeviation_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_larlitecLcLTrackDeviation(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::TrackDeviation : new ::larlite::TrackDeviation;
   }
   static void *newArray_larlitecLcLTrackDeviation(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::TrackDeviation[nElements] : new ::larlite::TrackDeviation[nElements];
   }
   // Wrapper around operator delete
   static void delete_larlitecLcLTrackDeviation(void *p) {
      delete ((::larlite::TrackDeviation*)p);
   }
   static void deleteArray_larlitecLcLTrackDeviation(void *p) {
      delete [] ((::larlite::TrackDeviation*)p);
   }
   static void destruct_larlitecLcLTrackDeviation(void *p) {
      typedef ::larlite::TrackDeviation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::larlite::TrackDeviation

namespace ROOT {
   // Wrappers around operator new
   static void *new_larlitecLcLGetDeviation(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::GetDeviation : new ::larlite::GetDeviation;
   }
   static void *newArray_larlitecLcLGetDeviation(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::larlite::GetDeviation[nElements] : new ::larlite::GetDeviation[nElements];
   }
   // Wrapper around operator delete
   static void delete_larlitecLcLGetDeviation(void *p) {
      delete ((::larlite::GetDeviation*)p);
   }
   static void deleteArray_larlitecLcLGetDeviation(void *p) {
      delete [] ((::larlite::GetDeviation*)p);
   }
   static void destruct_larlitecLcLGetDeviation(void *p) {
      typedef ::larlite::GetDeviation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::larlite::GetDeviation

namespace ROOT {
   static TClass *vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR_Dictionary();
   static void vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p = 0);
   static void *newArray_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p);
   static void deleteArray_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p);
   static void destruct_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<int,vector<double> > >*)
   {
      vector<pair<int,vector<double> > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<int,vector<double> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<int,vector<double> > >", -2, "vector", 477,
                  typeid(vector<pair<int,vector<double> > >), DefineBehavior(ptr, ptr),
                  &vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<pair<int,vector<double> > >) );
      instance.SetNew(&new_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<int,vector<double> > > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<pair<int,vector<double> > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<int,vector<double> > >*)0x0)->GetClass();
      vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<pair<int,vector<double> > > : new vector<pair<int,vector<double> > >;
   }
   static void *newArray_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<pair<int,vector<double> > >[nElements] : new vector<pair<int,vector<double> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p) {
      delete ((vector<pair<int,vector<double> > >*)p);
   }
   static void deleteArray_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p) {
      delete [] ((vector<pair<int,vector<double> > >*)p);
   }
   static void destruct_vectorlEpairlEintcOvectorlEdoublegRsPgRsPgR(void *p) {
      typedef vector<pair<int,vector<double> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<int,vector<double> > >

namespace ROOT {
   static TClass *vectorlEpairlEintcOdoublegRsPgR_Dictionary();
   static void vectorlEpairlEintcOdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEintcOdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEpairlEintcOdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEintcOdoublegRsPgR(void *p);
   static void deleteArray_vectorlEpairlEintcOdoublegRsPgR(void *p);
   static void destruct_vectorlEpairlEintcOdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<int,double> >*)
   {
      vector<pair<int,double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<int,double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<int,double> >", -2, "vector", 477,
                  typeid(vector<pair<int,double> >), DefineBehavior(ptr, ptr),
                  &vectorlEpairlEintcOdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<pair<int,double> >) );
      instance.SetNew(&new_vectorlEpairlEintcOdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEintcOdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEintcOdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEintcOdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEintcOdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<int,double> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<pair<int,double> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEintcOdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<int,double> >*)0x0)->GetClass();
      vectorlEpairlEintcOdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEintcOdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEintcOdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<pair<int,double> > : new vector<pair<int,double> >;
   }
   static void *newArray_vectorlEpairlEintcOdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<pair<int,double> >[nElements] : new vector<pair<int,double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEintcOdoublegRsPgR(void *p) {
      delete ((vector<pair<int,double> >*)p);
   }
   static void deleteArray_vectorlEpairlEintcOdoublegRsPgR(void *p) {
      delete [] ((vector<pair<int,double> >*)p);
   }
   static void destruct_vectorlEpairlEintcOdoublegRsPgR(void *p) {
      typedef vector<pair<int,double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<int,double> >

namespace ROOT {
   static TClass *vectorlEgeoalgocLcLTrajectorygR_Dictionary();
   static void vectorlEgeoalgocLcLTrajectorygR_TClassManip(TClass*);
   static void *new_vectorlEgeoalgocLcLTrajectorygR(void *p = 0);
   static void *newArray_vectorlEgeoalgocLcLTrajectorygR(Long_t size, void *p);
   static void delete_vectorlEgeoalgocLcLTrajectorygR(void *p);
   static void deleteArray_vectorlEgeoalgocLcLTrajectorygR(void *p);
   static void destruct_vectorlEgeoalgocLcLTrajectorygR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<geoalgo::Trajectory>*)
   {
      vector<geoalgo::Trajectory> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<geoalgo::Trajectory>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<geoalgo::Trajectory>", -2, "vector", 477,
                  typeid(vector<geoalgo::Trajectory>), DefineBehavior(ptr, ptr),
                  &vectorlEgeoalgocLcLTrajectorygR_Dictionary, isa_proxy, 0,
                  sizeof(vector<geoalgo::Trajectory>) );
      instance.SetNew(&new_vectorlEgeoalgocLcLTrajectorygR);
      instance.SetNewArray(&newArray_vectorlEgeoalgocLcLTrajectorygR);
      instance.SetDelete(&delete_vectorlEgeoalgocLcLTrajectorygR);
      instance.SetDeleteArray(&deleteArray_vectorlEgeoalgocLcLTrajectorygR);
      instance.SetDestructor(&destruct_vectorlEgeoalgocLcLTrajectorygR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<geoalgo::Trajectory> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<geoalgo::Trajectory>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEgeoalgocLcLTrajectorygR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<geoalgo::Trajectory>*)0x0)->GetClass();
      vectorlEgeoalgocLcLTrajectorygR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEgeoalgocLcLTrajectorygR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEgeoalgocLcLTrajectorygR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<geoalgo::Trajectory> : new vector<geoalgo::Trajectory>;
   }
   static void *newArray_vectorlEgeoalgocLcLTrajectorygR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<geoalgo::Trajectory>[nElements] : new vector<geoalgo::Trajectory>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEgeoalgocLcLTrajectorygR(void *p) {
      delete ((vector<geoalgo::Trajectory>*)p);
   }
   static void deleteArray_vectorlEgeoalgocLcLTrajectorygR(void *p) {
      delete [] ((vector<geoalgo::Trajectory>*)p);
   }
   static void destruct_vectorlEgeoalgocLcLTrajectorygR(void *p) {
      typedef vector<geoalgo::Trajectory> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<geoalgo::Trajectory>

namespace {
  void TriggerDictionaryInitialization_libShiYan_TrackAnalysis_Impl() {
    static const char* headers[] = {
"GetDeviation.h",
"TrackDeviation.h",
0
    };
    static const char* includePaths[] = {
"/Users/dayajun/LArLite/core",
"/Users/dayajun/LArLite/UserDev/BasicTool",
"/Users/dayajun/LArLite/UserDev/BasicTool",
"/Users/dayajun/LArLite/UserDev/SelectionTool",
"/Applications/BasicSoftware/root/v6_03_04/include",
"/Users/dayajun/LArLite/UserDev/ShiYan/TrackAnalysis/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace larlite{class __attribute__((annotate("$clingAutoload$GetDeviation.h")))  TrackDeviation;}
namespace larlite{class __attribute__((annotate("$clingAutoload$GetDeviation.h")))  GetDeviation;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "GetDeviation.h"
#include "TrackDeviation.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"larlite::GetDeviation", payloadCode, "@",
"larlite::TrackDeviation", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libShiYan_TrackAnalysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libShiYan_TrackAnalysis_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libShiYan_TrackAnalysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libShiYan_TrackAnalysis() {
  TriggerDictionaryInitialization_libShiYan_TrackAnalysis_Impl();
}
