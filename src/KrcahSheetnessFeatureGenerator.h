#ifndef __KrcahSheetnessFeatureGenerator_h_
#define __KrcahSheetnessFeatureGenerator_h_

#include "itkImageToImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkAddImageFilter.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkSymmetricEigenAnalysisImageFilter.h"
#include "itkStatisticsImageFilter.h"

#include "MaximumAbsoluteValueImageFilter.h"
#include "KrcahSheetnessImageFilter.h"
#include "TraceImageFilter.h"

namespace itk {
    template<typename TInput, typename TOutput>
    class ITK_EXPORT KrcahSheetnessFeatureGenerator : public ImageToImageFilter<TInput, TOutput> {
    public:
        typedef KrcahSheetnessFeatureGenerator Self;
        typedef ImageToImageFilter<TInput, TOutput> Superclass;
        typedef SmartPointer<Self> Pointer;
        typedef SmartPointer<const Self> ConstPointer;

        itkNewMacro(Self);

        itkTypeMacro(KrcahSheetnessFeatureGenerator, ImageToImageFilter);
        itkStaticConstMacro(NDimension, unsigned
                int, TInput::ImageDimension);

        typedef float InternalPixelType;
        typedef TInput InputImageType;
        typedef Image<InternalPixelType, NDimension> InternalImageType;
        typedef TOutput OutputImageType;

    protected:
        KrcahSheetnessFeatureGenerator();

        virtual ~KrcahSheetnessFeatureGenerator();

        void GenerateData();

    private:
        KrcahSheetnessFeatureGenerator(const Self &);

        void operator=(const Self &);

        typename OutputImageType::Pointer generateSheetnessWithSigma(typename InputImageType::ConstPointer img, float sigma);

        // input processing
        typedef CastImageFilter<InputImageType, InternalImageType> InputCastFilterType;
        typedef DiscreteGaussianImageFilter<InternalImageType, InternalImageType> GaussianFilterType;
        typedef SubtractImageFilter<InternalImageType, InternalImageType, InternalImageType> SubstractFilterType;
        typedef MultiplyImageFilter<InternalImageType, InternalImageType, InternalImageType> MultiplyFilterType;
        typedef AddImageFilter<InternalImageType, InternalImageType, InternalImageType> AddFilterType;

        // sheetness prerequisites
        typedef HessianRecursiveGaussianImageFilter<InternalImageType> HessianFilterType;
        typedef typename HessianFilterType::OutputImageType HessianImageType;
        typedef typename HessianImageType::PixelType HessianPixelType;
        typedef FixedArray<double, HessianPixelType::Dimension> EigenValueArrayType;
        typedef Image<EigenValueArrayType, NDimension> EigenValueImageType;
        typedef SymmetricEigenAnalysisImageFilter<HessianImageType, EigenValueImageType> EigenAnalysisFilterType;
        typedef TraceImageFilter<HessianImageType, InternalImageType> TraceFilterType;
        typedef StatisticsImageFilter<InternalImageType> StatisticsFilterType;

        // sheetness
        typedef KrcahSheetnessImageFilter<EigenValueImageType, double, OutputImageType> SheetnessFilterType;

        // post processing
        typedef MaximumAbsoluteValueImageFilter<OutputImageType, OutputImageType, OutputImageType> MaximumAbsoluteValueFilterType;

    };
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION

#include "KrcahSheetnessFeatureGenerator.hxx"

#endif

#endif //__KrcahSheetnessFeatureGenerator_h_