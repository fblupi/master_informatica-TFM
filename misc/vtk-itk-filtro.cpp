// Definir tipo de imagen ITK usando signed short y 3 dimensiones
typedef signed short PixelType;
const unsigned int Dimension = 3;
typedef itk::Image<PixelType,Dimension> ImageType;

// Crear pipeline para pasar una imagen VTK a ITK
typedef itk::VTKImageToImageFilter<ImageType> VTKImageToImageType;
VTKImageToImageType::Pointer vtkImageToImage = VTKImageToImageType::New();
vtkImageToImage->SetInput(imageData);
vtkImageToImage->Update();

// Filtrar la imagen ITK usando un filtro media
typedef itk::MeanImageFilter<ImageType,ImageType> MeanImageFilterType;
MeanImageFilterType::Pointer meanFilter = MeanImageFilterType::New();
meanFilter->SetInput(vtkImageToImage->GetOutput());
meanFilter->SetRadius(radius);
meanFilter->Update();

// Pasara de imagen ITK filtrada a VTK
typedef itk::ImageToVTKImageFilter<ImageType> ImageToVTKImageType;
ImageToVTKImageType::Pointer imageToVTKImage = ImageToVTKImageType::New();
imageToVTKImage->SetInput(meanFilter->GetOutput());
imageToVTKImage->Update();

// Actualizar la instancia de la imagen VTK
imageData->DeepCopy(imageToVTKImage->GetOutput());
imageData->Modified();