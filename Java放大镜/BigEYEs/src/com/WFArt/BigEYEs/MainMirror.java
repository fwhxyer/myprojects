package com.WFArt.BigEYEs;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.Random;

import javax.swing.*;

public class MainMirror extends JPanel{
	/**/
	private static final long serialVersionUID = 1L;
	private BufferedImage background;
	private int x,y,size,time=2,fix=2;
	private Robot getBackground;
	private int eyeSize=250;
	
	public MainMirror(int sizesize) {
	    try{getBackground = new Robot();} catch(AWTException e){}    
		background = getBackground.createScreenCapture(new Rectangle(0,0,Toolkit.getDefaultToolkit().getScreenSize().width,Toolkit.getDefaultToolkit().getScreenSize().height));
		eyeSize=sizesize;
		size=1+sizesize/100;
		fix=sizesize/100;
		setPreferredSize(new Dimension(size,size));
	}
	
	public void setBigTimes(int a){
		this.time=a;
	    repaint();
	}

	public void setLocation(int xx,int yy){
		this.x = xx;
	    this.y = yy;
	    repaint();
	}
	//-------------------------------------改变显示效果----------------------------
	public void setType(int type){
		if (type!=2&&type!=3)
			background = getBackground.createScreenCapture(new Rectangle(0,0,Toolkit.getDefaultToolkit().getScreenSize().width,Toolkit.getDefaultToolkit().getScreenSize().height));
		if (type==2) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_4BYTE_ABGR_PRE); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {
	            	int tmp=background.getRGB(x,y);
	            	Color tmpC=new Color(tmp);
	            	tmpC=tmpC.brighter();
	            	tmp=tmpC.getRGB();
	            	nbi.setRGB(x, y, tmp);
	            }  
	        }  
	        background=nbi;
		}
		if (type==3) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_4BYTE_ABGR_PRE); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {
	            	int tmp=background.getRGB(x,y);
	            	Color tmpC=new Color(tmp);
	            	tmpC=tmpC.darker();
	            	tmp=tmpC.getRGB();
	            	nbi.setRGB(x, y, tmp);
	            }  
	        }  
	        background=nbi;
		}
		if (type==4) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        int mid=190;
	        int rgb=new Color(mid,mid,mid).getRGB();
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_BYTE_BINARY); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {  
	                if(background.getRGB(x, y)>rgb){  
	                    int max=new Color(255,255,255).getRGB();  
	                    nbi.setRGB(x, y, max);  
	                }else{  
	                    int min=new Color(0,0,0).getRGB();  
	                    nbi.setRGB(x, y, min);  
	                }  
	            }  
	        }  
	        background=nbi;
		}
		if (type==5) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_4BYTE_ABGR_PRE); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {
	            	int tmp=background.getRGB(x,y);
	            	Color tmpC=new Color(tmp);
	            	int r=tmpC.getRed();
	            	int g=tmpC.getGreen();
	            	int b=tmpC.getBlue();
	            	r=255-r;
	            	g=255-g;
	            	b=255-b;
	            	tmp=new Color(r,g,b).getRGB();
	            	nbi.setRGB(x, y, tmp);
	            }  
	        }  
	        background=nbi;
		}
		if (type==6) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_4BYTE_ABGR_PRE); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {
	            	int tmp=background.getRGB(x,y);
	            	Color tmpC=new Color(tmp);
	            	Random rand=new Random();
	            	int randSize=30;
	            	int r=tmpC.getRed()+rand.nextInt()%randSize;
	            	int g=tmpC.getGreen()+rand.nextInt()%randSize;
	            	int b=tmpC.getBlue()+rand.nextInt()%randSize;
	            	if (r<0) r=0;
	            	if (r>255) r=255;
	            	if (g<0) g=0;
	            	if (g>255) g=255;
	            	if (b<0) b=0;
	            	if (b>255) b=255;
	            	tmp=new Color(r,g,b).getRGB();
	            	nbi.setRGB(x, y, tmp);
	            }  
	        }  
	        background=nbi;
		}
		if (type==7) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_4BYTE_ABGR_PRE); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {
	            	int tmp=background.getRGB(x,y);
	            	Color tmpC=new Color(tmp);
	            	Random rand=new Random();
	            	int randSize=200;
	            	int r=tmpC.getRed()+rand.nextInt()%randSize;
	            	int g=tmpC.getGreen()+rand.nextInt()%randSize;
	            	int b=tmpC.getBlue()+rand.nextInt()%randSize;
	            	if (r<0) r=0;
	            	if (r>255) r=255;
	            	if (g<0) g=0;
	            	if (g>255) g=255;
	            	if (b<0) b=0;
	            	if (b>255) b=255;
	            	tmp=new Color(r,g,b).getRGB();
	            	nbi.setRGB(x, y, tmp);
	            }  
	        }  
	        background=nbi;
		}
		if (type==8) {
			int h=background.getHeight();
	        int w=background.getWidth();  
	        BufferedImage nbi=new BufferedImage(w,h,BufferedImage.TYPE_BYTE_GRAY); 
	        for (int x = 0; x < w; x++) {  
	            for (int y = 0; y < h; y++) {
	            	int tmp=background.getRGB(x,y);
	            	Color tmpC=new Color(tmp);
	            	int r=tmpC.getRed();
	            	int g=tmpC.getGreen();
	            	int b=tmpC.getBlue();
	            	tmp=(r+g+b)/3;
	            	tmp=new Color(tmp,tmp,tmp).getRGB();
	            	nbi.setRGB(x, y, tmp);
	            }  
	        }  
	        background=nbi;
		}
		repaint();  
	}
	//-------------------------------------改变显示效果----------------------------
	public void setImage(BufferedImage screenImage){
		this.background = screenImage;
		repaint();  
	}
	public void paintComponent(Graphics g){
		super.paintComponent((Graphics2D)g);  
		drawScreenRectangle((Graphics2D)g);
	}
	private void drawScreenRectangle(Graphics2D g){
	    g.drawImage(background,
	                 0,
	                 0,
	                 eyeSize,
	                 eyeSize,
	                 fix+x,
	                 fix+y,
	                 fix+x+eyeSize/time,
	                 fix+y+eyeSize/time,
	                 this);
	}
}
