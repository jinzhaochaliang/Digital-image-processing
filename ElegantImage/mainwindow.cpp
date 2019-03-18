#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editimage.h"
#include "drawwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    MainWindow::editimagewindow = new editimage;
    connect(editimagewindow,SIGNAL(sendMat(Mat)),this,SLOT(receiveMat(Mat)));
    MainWindow::drawwindow = new drawWindow;
    connect(drawwindow,SIGNAL(sendMat(Mat)),this,SLOT(receiveMat(Mat)));

    ShowLabelslot();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::receiveMat(Mat data){
    image = data.clone();
    updateimage();
}
void MainWindow::ShowLabelslot()
{
    connect(ui->original,SIGNAL(clicked(bool)),this,SLOT(clearimageslot()));//清空
    connect(ui->black,SIGNAL(clicked(bool)),this,SLOT(blackandwhiteslot()));//黑白
    connect(ui->relievo,SIGNAL(clicked(bool)),this,SLOT(relievoslot()));//浮雕
    connect(ui->reminiscence,SIGNAL(clicked(bool)),this,SLOT(reminiscenceslot()));//怀旧
    connect(ui->binaryzation,SIGNAL(clicked(bool)),this,SLOT(binaryzationslot()));//木刻
    connect(ui->sketch,SIGNAL(clicked(bool)),this,SLOT(sketchslot()));//素描
    connect(ui->line,SIGNAL(clicked(bool)),this,SLOT(lineslot()));//线条
    connect(ui->glass,SIGNAL(clicked(bool)),this,SLOT(glassslot()));//毛玻璃
    connect(ui->corrosion,SIGNAL(clicked(bool)),this,SLOT(corrosionslot()));//腐蚀
    connect(ui->swell,SIGNAL(clicked(bool)),this,SLOT(swellslot()));//膨胀
    connect(ui->cartoon,SIGNAL(clicked(bool)),this,SLOT(cartoonizeslot()));//卡通

    connect(ui->add,SIGNAL(clicked()),this,SLOT(openfileslot()));//打开
//    connect(ui->add,SIGNAL(clicked()),this,SLOT(AddButtonHideslot()));//打开按钮消失
    connect(ui->laststep,SIGNAL(clicked(bool)),this,SLOT(laststepslot()));//上一步
}
void MainWindow::AddButtonHideslot()
{
    ui->add->hide();
}
void MainWindow::createActions(){

    openAction = new QAction(QIcon(":/new/prefix1/pic/add.png"),tr("打开"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openfileslot()));
    saveAction = new QAction(QIcon(":/new/prefix1/pic/save.png"),tr("保存"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveslot()));
    exitAction = new QAction(QIcon(":/new/prefix1/pic/退出.png"),tr("退出"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exitslot()));
    clearAction = new QAction(QIcon(":/new/prefix1/pic/撤销.png"),tr("清空"));
    connect(clearAction,SIGNAL(triggered()),this,SLOT(clearimageslot()));
    laststepAction = new QAction(QIcon(":/new/prefix1/pic/上一步.png"),tr("上一步"));
    connect(laststepAction,SIGNAL(triggered()),this,SLOT(laststepslot()));
    nextstepAction = new QAction(QIcon(":/new/prefix1/pic/下一步.png"),tr("下一步"));
    connect(nextstepAction,SIGNAL(triggered()),this,SLOT(nextstepslot()));

    rotateAction = new QAction(QIcon(":/new/prefix1/pic/旋转.png"),tr("旋转"));
    connect(rotateAction,SIGNAL(triggered()),this,SLOT(rotateslot()));
    brightnessAction = new QAction(QIcon(":/new/prefix1/pic/调整.png"),tr("调整"));
    connect(brightnessAction,SIGNAL(triggered()),this,SLOT(brightnessslot()));
    sharpenAction=new QAction(QIcon(":/new/prefix1/pic/锐化.png"),tr("锐化"));
    connect(sharpenAction,SIGNAL(triggered()),this,SLOT(sharpenslot()));
    awbAction=new QAction(QIcon(":/new/prefix1/pic/白平衡.png"),tr("白平衡"));
    connect(awbAction,SIGNAL(triggered()),this,SLOT(awbslot()));
    colortranAction = new QAction(QIcon(":/new/prefix1/pic/colortran.jpg"),tr("颜色转移"));
    connect(colortranAction,SIGNAL(triggered()),this,SLOT(colortranslot()));

    blackandwhiteAction = new QAction(tr("黑白"));
    connect(blackandwhiteAction,SIGNAL(triggered()),this,SLOT(blackandwhiteslot()));
    relievoAction = new QAction(tr("浮雕"));
    connect(relievoAction,SIGNAL(triggered()),this,SLOT(relievoslot()));
    reminiscenceAction = new QAction(tr("怀旧"));
    connect(reminiscenceAction,SIGNAL(triggered()),this,SLOT(reminiscenceslot()));
    binaryzationAction = new QAction(tr("木刻"));
    connect(binaryzationAction,SIGNAL(triggered()),this,SLOT(binaryzationslot()));
    sketchAction = new QAction(tr("素描"));
    connect(sketchAction, SIGNAL(triggered()),this,SLOT(sketchslot()));
    lineAction = new QAction(tr("线条"));
    connect(lineAction, SIGNAL(triggered()),this,SLOT(lineslot()));
    glassAction=new QAction(tr("毛玻璃"));
    connect(glassAction,SIGNAL(triggered()),this,SLOT(glassslot()));
    corrosionAction=new QAction(tr("碎片"));//腐蚀
    connect(corrosionAction,SIGNAL(triggered()),this,SLOT(corrosionslot()));
    swellAction=new QAction(tr("亮斑"));//膨胀
    connect(swellAction,SIGNAL(triggered()),this,SLOT(swellslot()));
    cartoonAction=new QAction(tr("卡通"));
    connect(cartoonAction,SIGNAL(triggered()),this,SLOT(cartoonizeslot()));


    buffingAction = new QAction(QIcon(":/new/prefix1/pic/磨皮.png"),tr("磨皮"));
    connect(buffingAction,SIGNAL(triggered()),this,SLOT(buffingslot()));
    thinfaceAction = new QAction(QIcon(":/new/prefix1/pic/瘦脸.png"),tr("瘦脸"));
    connect(thinfaceAction,SIGNAL(triggered()),this,SLOT(thinfaceslot()));
    skinwhiteningAction = new QAction(QIcon(":/new/prefix1/pic/美白.png"),tr("美白"));
    connect(skinwhiteningAction,SIGNAL(triggered()),this,SLOT(skinwhiteningslot()));
    eyeAction = new QAction(QIcon(":/new/prefix1/pic/eye.png"),tr("大眼睛"));
    connect(eyeAction,SIGNAL(triggered()),this,SLOT(eyeslot()));
    cuteAction = new QAction(QIcon(":/new/prefix1/pic/meng.png"),tr("萌宠图标"));
    connect(cuteAction,SIGNAL(triggered()),this,SLOT(cuteslot()));
    ChristmasAction = new QAction(QIcon(":/new/prefix1/pic/chrismas.png"),tr("圣诞帽"));
    connect(ChristmasAction,SIGNAL(triggered()),this,SLOT(Christmasslot()));

    paintAction = new QAction(QIcon(":/new/prefix1/pic/绘画.png"),tr("涂鸦"));
    connect(paintAction,SIGNAL(triggered()),this,SLOT(paintslot()));
}

void MainWindow::createMenus(){

    fileMenu = ui->menuBar->addMenu(tr("文件"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(clearAction);
    fileMenu->addAction(laststepAction);
    fileMenu->addAction(nextstepAction);
    fileMenu->addAction(exitAction);

    editMenu = ui->menuBar->addMenu(tr("编辑"));
    editMenu->addAction(rotateAction);
    editMenu->addAction(brightnessAction);
    editMenu->addAction(sharpenAction);
    editMenu->addAction(awbAction);
    editMenu->addAction(colortranAction);

    filterMenu = ui->menuBar->addMenu(tr("滤镜"));
    filterMenu->addAction(blackandwhiteAction);
    filterMenu->addAction(relievoAction);
    filterMenu->addAction(reminiscenceAction);
    filterMenu->addAction(binaryzationAction);
    filterMenu->addAction(sketchAction);
    filterMenu->addAction(lineAction);
    filterMenu->addAction(glassAction);
    filterMenu->addAction(corrosionAction);
    filterMenu->addAction(swellAction);
    filterMenu->addAction(cartoonAction);


    beautyMenu = ui->menuBar->addMenu(tr("美肤"));
    beautyMenu->addAction(buffingAction);
    beautyMenu->addAction(thinfaceAction);
    beautyMenu->addAction(skinwhiteningAction);
    beautyMenu->addAction(eyeAction);
    beautyMenu->addAction(cuteAction);
    beautyMenu->addAction(ChristmasAction);

    drawMenu = ui->menuBar->addMenu(tr("绘图"));
    drawMenu->addAction(paintAction);
}
static QImage cvMat_to_QImage(const cv::Mat &mat ) {
  switch ( mat.type() )
  {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( mat.data, mat.cols, mat.rows, int(mat.step), QImage::Format_RGB32 );
        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( mat.data, mat.cols, mat.rows, int(mat.step), QImage::Format_RGB888 );
        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
        static QVector<QRgb>  sColorTable;
        // only create our color table once
        if ( sColorTable.isEmpty() )
        {
           for ( int i = 0; i < 256; ++i )
              sColorTable.push_back( qRgb( i, i, i ) );
        }
        QImage image( mat.data, mat.cols, mat.rows, int(mat.step), QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
        return image;
     }

     default:
        qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
        break;
  }
  return QImage();
}
void MainWindow::openfileslot(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    if(!fileName.isEmpty())
    {
        image = imread(fileName.toLatin1().data());
        imagetemp = imread(fileName.toLatin1().data());
        matstack.push(image);
        if(!image.data)
        {
            QMessageBox::warning(this, tr("警告"),tr("图片打开失败"));
            return;
        }
        else
        {
            ui->add->hide();
            QImage img = cvMat_to_QImage(image);
            QPixmap pixmap = QPixmap::fromImage(img);
            pixmap = pixmap.scaled(ui->Imagelabel->width(),
                                   ui->Imagelabel->height(),
                                   Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);
            ui->Imagelabel->setPixmap(pixmap);
            ui->Updatelabel->setPixmap(pixmap);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("警告"),tr("请选择文件"));
        return;
    }
}

void MainWindow::rotateslot()
{
    transpose(image, image);//逆时针旋转90，镜像
    flip(image,image,0);//x轴（0）翻转
    updateimage();
}
void MainWindow::brightnessslot(){
    editimagewindow->editmat = image.clone();
    editimagewindow->edittempmat = image.clone();
    editimagewindow->updateeditimage();
    editimagewindow->show();
}
void MainWindow::sharpenslot()
{
    Mat temp = image.clone();
    Mat kern = (Mat_<char>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
    filter2D(temp,temp,temp.depth(),kern);
    image = temp.clone();
    updateimage();
}
void MainWindow::awbslot(){
    vector <Mat> imageRGB;
    Mat temp = image.clone();
    split(temp,imageRGB);
    double R,G,B;
    B=mean(imageRGB[0])[0];
    G=mean(imageRGB[1])[0];
    R=mean(imageRGB[2])[0];
    double KR, KG, KB;
    KB = (R + G + B) / (3 * B);
    KG = (R + G + B) / (3 * G);
    KR = (R + G + B) / (3 * R);
    imageRGB[0] = imageRGB[0] * KB;
    imageRGB[1] = imageRGB[1] * KG;
    imageRGB[2] = imageRGB[2] * KR;
    merge(imageRGB,temp);

    image = temp.clone();
    updateimage();
}
void MainWindow::colortranslot(){
    /*
     *
     * 将参考图像和目标图像转换到LAB颜色空间下
     * 计算参考图像和目标图像的均值和标准差
     * 目标图像的每个像素值，减去目标图像的均值然后乘以参考图像和目标图像标准差的比值，再加上参考图像的均值
     * 目标图像转换到RGB空间
     *
     */
    Mat temp = image.clone();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    if(!fileName.isEmpty())
    {
        Mat targ = imread(fileName.toLatin1().data());
        Mat result = colortran(temp,targ);
        image = result.clone();
        updateimage();
    }
}
void MainWindow::paintslot(){
    drawwindow->drawmat = image.clone();
    drawwindow->drawtempmat = image.clone();
    drawwindow->updateslot();
    drawwindow->show();
}
void MainWindow::blackandwhiteslot(){
    if(image.type()==CV_8UC3){
        cvtColor(image,image,COLOR_BGR2GRAY);
    }
    updateimage();
}
void MainWindow::relievoslot(){
    Mat kern = (Mat_<char>(3,3)<<-1,-4,-1,0,0,0,1,4,1);
    if(image.type()==CV_8UC3){
        cvtColor(image,image,COLOR_BGR2GRAY);
    }
    filter2D(image,image,image.depth(),kern);
    updateimage();
}
void MainWindow::binaryzationslot(){
    if(image.type()==CV_8UC3){
        cvtColor(image,image,COLOR_BGR2GRAY);
    }
    threshold(image,image,127,255,THRESH_BINARY);
    updateimage();
}
void MainWindow::reminiscenceslot(){
    if(image.type()==CV_8UC3){
        Mat temp = image.clone();
        for(int y=0;y<temp.rows;y++){
            uchar* p = temp.ptr<uchar>(y);
            for(int x=0;x<temp.cols;x++){
                int b = p[x*3];
                int g = p[x*3+1];
                int r = p[x*3+2];
                int R = static_cast<int>(0.393*r+0.769*g+0.189*b);
                int G = static_cast<int>(0.349*r+0.686*g+0.168*b);
                int B = static_cast<int>(0.272*r+0.534*g+0.131*b);
                p[x*3+2] = uchar(max(0,min(R,255)));
                p[x*3+1] = uchar(max(0,min(G,255)));
                p[x*3] = uchar(max(0,min(B,255)));
            }
        }
        image = temp.clone();
        updateimage();
    }
}
void MainWindow::lineslot(){
    /*
     * 图像灰度化
     * 滤波
     * 边缘检测
     * 二值化
     */
    if(image.type()==CV_8UC3){
        cvtColor(image,image,COLOR_BGR2GRAY);
    }
    medianBlur(image,image,7);
    Laplacian(image,image,CV_8U,5);
    threshold(image,image,127,255,THRESH_BINARY_INV);
    updateimage();
}
void MainWindow::glassslot(){
//    毛玻璃 ->高斯模糊 扩散
    if(image.type()==CV_8UC3){
        Mat temp = image.clone();
        int width=temp.cols;
        int height=temp.rows;
        RNG rng;//随机数类rng,类似rand()
        for(int y=0;y<height-5;y++)
        {
            for (int x=0; x<width-5; x++)
            {
                int tmp=rng.uniform(0,5);
                temp.ptr<uchar>(y,x)[0]=temp.ptr<uchar>(y+tmp,x+tmp)[0];
                temp.ptr<uchar>(y,x)[1]=temp.ptr<uchar>(y+tmp,x+tmp)[1];
                temp.ptr<uchar>(y,x)[2]=temp.ptr<uchar>(y+tmp,x+tmp)[2];
            }
        }
        image = temp.clone();
        updateimage();
    }
}
void MainWindow::corrosionslot()
{
    if(image.type()==CV_8UC3){
        Mat temp = image.clone();
        Mat element=getStructuringElement(MORPH_RECT,Size(10,10));//MORPH_RECT表示矩形的卷积核
        //腐蚀
        erode(temp,temp,element);
        image=temp.clone();
        updateimage();
    }
}
void MainWindow::swellslot()
{
    Mat temp = image.clone();
    Mat element=getStructuringElement(MORPH_RECT,Size(10,10));
    //膨胀
    dilate(temp,temp,element);
    image=temp.clone();
    updateimage();
}
void MainWindow::cartoonizeslot()
{
    if(image.type()==CV_8UC3){
        Mat imgMedian;
        medianBlur(image,imgMedian,7);
        Mat imgCanny;
        Canny(imgMedian,imgCanny,50,150);
         Mat kernel=getStructuringElement(MORPH_RECT,Size(2,2));
        dilate(imgCanny,imgCanny,kernel);
        imgCanny=imgCanny/255;
        imgCanny=1-imgCanny;
        Mat imgCannyf;
        imgCanny.convertTo(imgCannyf,CV_32FC3);
        blur(imgCannyf,imgCannyf,Size(5,5));
        Mat imgBF;
        bilateralFilter(image, imgBF, 9, 150.0, 150.0);
        Mat result=imgBF/25;
        result=result*25;
        Mat imgCanny3c;
        Mat cannyChannels[] = { imgCannyf, imgCannyf, imgCannyf };
        merge(cannyChannels, 3, imgCanny3c);
        Mat resultf;
        result.convertTo(resultf,CV_32FC3);
        multiply(resultf,imgCanny3c,resultf);
        resultf.convertTo(result,CV_8UC3);
        image=result.clone();
        updateimage();
    }

}

void MainWindow::sketchslot(){
    /*
     * 将图像转换成黑白颜色
     * 复制图像，并对复制后的图像反相
     * 将复制后的图像做高斯模糊
     * 将模糊后的图像与原图像以颜色减淡模式混合
     *
     */
    Mat gray0,gray1;
    if(image.type()==CV_8UC3){
        cvtColor(image,gray0,COLOR_BGR2GRAY);

        addWeighted(gray0,-1,NULL,0,255,gray1);
        //反色
        GaussianBlur(gray1,gray1,Size(11,11),0);
        //高斯模糊
        Mat img(gray1.size(),CV_8UC1);
        for(int y=0;y<image.rows;y++){
            uchar* p0 = gray0.ptr<uchar>(y);
            uchar* p1 = gray1.ptr<uchar>(y);
            uchar* p = img.ptr<uchar>(y);
            for(int x=0;x<image.cols;x++){
                int temp0 = p0[x];
                int temp1 = p1[x];
                p[x] = uchar(min((temp0+(temp0*temp1)/(256-temp1)),255));
            }
        }
        image = img.clone();
        updateimage();
    }
}
void MainWindow::Christmasslot(){
    Mat temp = image.clone();
    CascadeClassifier ccf; //创建分类器对象
    if(!ccf.load(facePath)) //加载训练文件
    {
        cout<<"不能加载指定的xml文件"<<endl;
    }
    vector<Rect> faces; //创建一个容器保存检测出来的脸
    Mat gray;
    cvtColor(temp,gray,COLOR_BGR2GRAY); //转换成灰度图，因为harr特征从灰度图中提取
    equalizeHist(gray,gray); //直方图均衡行
    ccf.detectMultiScale(gray,faces,1.1,3,0,Size(10,10),Size(100,100)); //检测人脸
    for(size_t i=0;i<faces.size();i++){
        Mat hat = imread("hat.png");
        cv::resize(hat,hat,Size(faces.at(i).height,faces.at(i).width));
        Mat mask;
        cvtColor(hat,mask,COLOR_BGR2GRAY);
        Mat ROI = temp(Rect(faces.at(i).x,faces.at(i).y-int(hat.rows*0.5),hat.cols,hat.rows));
        hat.copyTo(ROI,mask);
    }
    image = temp.clone();
    updateimage();
}
void MainWindow::cuteslot(){
    CascadeClassifier ccf; //创建分类器对象
    if(!ccf.load(facePath)) //加载训练文件
    {
        cout<<"不能加载指定的xml文件"<<endl;
    }
    vector<Rect> faces; //创建一个容器保存检测出来的脸
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY); //转换成灰度图，因为harr特征从灰度图中提取
    equalizeHist(gray,gray); //直方图均衡行
    ccf.detectMultiScale(gray,faces,1.1,3,0,Size(10,10),Size(100,100)); //检测人脸
    for(vector<Rect>::const_iterator iter=faces.begin();iter!=faces.end();iter++)
    {
        rectangle(image,*iter,Scalar(0,0,255),2,8); //画出脸部矩形
    }
    updateimage();
}
void MainWindow::buffingslot(){
    /*
     *
     * 双边模糊
     * 高斯模糊
     * 图像增强
     */
    Mat dst = image.clone();
    int value1 = 2, value2 = 1;     //磨皮程度与细节程度的确定
    int dx = value1 * 5;    //双边滤波参数之一
    double fc = value1*12.5; //双边滤波参数之一
    int p = 50; //透明度
    Mat temp;
    bilateralFilter(dst, temp, dx, fc, fc);//双边滤波
    temp = (temp - dst + 128);
    GaussianBlur(temp, temp, Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);//高斯模糊
    temp = dst + 2 * temp - 255;
    dst = (dst*(100 - p) + temp*p) / 100;
    image = dst.clone();
    updateimage();
}
void MainWindow::thinfaceslot(){
//    std::vector<Rect> face;
//    CascadeClassifier face_cascade;
//    Mat temp = image.clone();
//    Mat tempgray;
//    Mat ROI;
//    if(!face_cascade.load(facePath)){
//        cout<<"face加载失败";
//    }else{
////        cout<<"face ok";
//    }
//    cvtColor(temp,tempgray,COLOR_BGR2GRAY);
//    face_cascade.detectMultiScale(tempgray,face,1.1,2,0,Size(30,30));
//    for(vector<Rect>::const_iterator iter=face.begin();iter!=face.end();iter++)
//    {
//        rectangle(temp,*iter,Scalar(0,0,255),2,8);
//    }
//    image = temp.clone();
//    updateimage();
}
void MainWindow::skinwhiteningslot(){
    Mat temp = image.clone();
    balancecolor(temp,40);
    image = temp.clone();
    updateimage();
}
void MainWindow::balancecolor(Mat& bitmap,int value)
{
    double  highlights_add[256], highlights_sub[256];
    double  midtones_add[256], midtones_sub[256];
    double  shadows_add[256], shadows_sub[256];
    for (int i = 0; i < 256; i++)
    {
        highlights_add[i] = shadows_sub[255 - i] = (1.075 - 1 / (double(i) / 16.0 + 1));
        midtones_add[i] = midtones_sub[i] = 0.667 * (1 - ((double(i) - 127.0) / 127.0)*((double(i) - 127.0) / 127.0));
        shadows_add[i] = highlights_sub[i] = 0.667 * (1 - ((double(i)- 127.0) / 127.0)*((double(i) - 127.0) / 127.0));
    }
    int red, green, blue;
    unsigned char r_lookup[256],g_lookup[256],b_lookup[256];

    for (int i = 0; i < 256; i++)
    {
        red = i;
        green = i;
        blue = i;

        red += int( 0.0 * shadows_sub[red] + value * midtones_add[red] + 0.0 * highlights_sub[red]);
        red = max(0,min(0xFF,red));

        green += int( 0.0 * shadows_sub[green] + value * midtones_add[green] + 0.0 * highlights_sub[green]);
        green = max(0,min(0xFF,green));

        blue += int( 0.0 * shadows_sub[blue] + value * midtones_add[blue] + 0.0 * highlights_sub[blue]);
        blue = max(0,min(0xFF,blue));

        r_lookup[i] = uchar(red);
        g_lookup[i] = uchar(green);
        b_lookup[i] = uchar(blue);
    }

    for (int row = 0; row < bitmap.rows; row++)
    {
        for (int col = 0; col < bitmap.cols; col++)
        {
            bitmap.at<Vec3b>(row, col)[0] = b_lookup[bitmap.at<Vec3b>(row, col)[0]];
            bitmap.at<Vec3b>(row, col)[1] = g_lookup[bitmap.at<Vec3b>(row, col)[1]];
            bitmap.at<Vec3b>(row, col)[2] = r_lookup[bitmap.at<Vec3b>(row, col)[2]];
        }
    }
}
void MainWindow::eyeslot(){
    std::vector<Rect> eyes;
    CascadeClassifier eyes_cascade;
    Mat temp = image.clone();
    Mat tempgray;
    Mat ROI;
    if(!eyes_cascade.load(eyePath)){
        cout<<"eyes加载失败";
    }else{
//        cout<<"eyes ok";
    }
    cvtColor(temp,tempgray,COLOR_BGR2GRAY);
    eyes_cascade.detectMultiScale(tempgray,eyes,1.1,2,0,Size(30,30));
//    for(vector<Rect>::const_iterator iter=eyes.begin();iter!=eyes.end();iter++)
//    {
//        rectangle(temp,*iter,Scalar(0,0,255),2,8);
//    }
    if(eyes.size()>0){
        for(size_t i=0;i<eyes.size();i++){
            Rect eye = eyes[i];
            ROI = temp(eye);
            cv::resize(ROI,ROI,Size(int(eye.height*1.1),int(eye.width*1.1)));
            ROI.copyTo(temp(Rect(eye.x- (int(eye.height*1.1)-ROI.cols)/2, eye.y - (int(eye.width*1.1)- ROI.rows)/2, ROI.cols, ROI.rows)));
        }
    }
    image = temp.clone();
    updateimage();
}
void MainWindow::clearimageslot(){
    image = imagetemp.clone();
    updateimage();
}
void MainWindow::updateimage(){
    matstack.push(image);
    mattempstack.clear();
    QImage img = cvMat_to_QImage(image);
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(ui->Imagelabel->width(),
                           ui->Imagelabel->height(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    ui->Updatelabel->setPixmap(pixmap);
}
void MainWindow::laststepslot(){
    if(matstack.size()>1){
        mattempstack.push(matstack.pop());
        image = matstack.top();
        QImage img = cvMat_to_QImage(image);
        QPixmap pixmap = QPixmap::fromImage(img);
        pixmap = pixmap.scaled(ui->Imagelabel->width(),
                               ui->Imagelabel->height(),
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
        ui->Updatelabel->setPixmap(pixmap);
    }
}
void MainWindow::nextstepslot(){
    if(!mattempstack.isEmpty()){
        image = mattempstack.pop();
        matstack.push(image);
        QImage img = cvMat_to_QImage(image);
        QPixmap pixmap = QPixmap::fromImage(img);
        pixmap = pixmap.scaled(ui->Imagelabel->width(),
                               ui->Imagelabel->height(),
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
        ui->Updatelabel->setPixmap(pixmap);
    }
}
void MainWindow::saveslot(){
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    imwrite(fileName.toLatin1().data(),image);
}
void MainWindow::exitslot(){
    qApp->quit();
}
