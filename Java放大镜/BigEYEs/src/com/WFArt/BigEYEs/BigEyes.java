package com.WFArt.BigEYEs;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class BigEyes extends JFrame{
	/*
	 */
	private static final long serialVersionUID = 1L;
	private BigEyes bigEyes;
	private int time=2;
	private boolean mousePressed;
	private int mirrorClickX,mirrorClickY;
	private MainMirror mainMirror;
	private ImageIcon background;
	public BigEyes() {
		bigEyes=this;
		this.setBackground(255);
		this.setLayout(null);
		this.setTitle("放大镜");
		this.setUndecorated(true);
		mainMirror = new MainMirror(250);
		mainMirror.setBounds(2,2,250,250);
		this.add(mainMirror);
		this.setBounds(500,200,255,255);
		this.setVisible(true);
		//this.setUndecorated(true);
		this.addMouseListener(
				new MouseAdapter()
				{
				    public void mousePressed(MouseEvent e){
			    		mousePressed = false;    
				        if (e.getClickCount()==1){
				        	mousePressed = true;  
				        	mirrorClickX=e.getX();
				            mirrorClickY=e.getY();
							System.out.printf("Press\n");
				        }
				        if (e.getClickCount()==2&&e.getButton()==MouseEvent.BUTTON1){
				    		bigEyes.setBounds( bigEyes.getLocationOnScreen().x, bigEyes.getLocationOnScreen().y,255,255);
				            bigEyes.setVisible(false);
				            bigEyes.remove(mainMirror);
				    		mainMirror = new MainMirror(250);
				    		mainMirror.setBounds(2,2,250,250);
				    		time=2;
				    		mainMirror.setBigTimes(time);
				    		bigEyes.add(mainMirror);
				    		bigEyes.setBackground(255);
				            bigEyes.setVisible(true);
							System.out.printf("Press b1\n");
				        }
				        if (e.getClickCount()==1&&e.getButton()!=MouseEvent.BUTTON1){
				        	mousePressed = true;  
				        	mirrorClickX=e.getX();
				            mirrorClickY=e.getY();
							System.out.printf("Press2\n");
				        }
				        if (e.getClickCount()==2&&e.getButton()!=MouseEvent.BUTTON1){
				    		bigEyes.setBounds( bigEyes.getLocationOnScreen().x, bigEyes.getLocationOnScreen().y,510,510);
				            bigEyes.setVisible(false);
				            bigEyes.remove(mainMirror);
				    		mainMirror = new MainMirror(500);
				    		bigEyes.setBackground(510);
				    		mainMirror.setBounds(5,5,500,500);
				    		time=5;
				    		mainMirror.setBigTimes(time);
				    		bigEyes.add(mainMirror);
				            bigEyes.setVisible(true);
							System.out.printf("Press b2\n");
				        }
				    }
				    public void mouseReleased(MouseEvent e){
				    	if (e.getButton()==MouseEvent.BUTTON1)
				    		mousePressed = false;    
			    	}
				}
			);	
		//==========================================================================================================
		this.addMouseWheelListener(
				new MouseWheelListener()
				{
				    public void mouseWheelMoved(MouseWheelEvent e){
				    	if (e.getWheelRotation()>0)
				    	{
							System.out.printf("roll -- \n");
							if (time>1)
								mainMirror.setBigTimes(--time);
				    	}
				    	if (e.getWheelRotation()<0)
				    	{
							System.out.printf("roll ++\n");
							if (time<25)
								mainMirror.setBigTimes(++time);
				    	}
				    }
				}
			);	
		//==========================================================================================================
		this.addMouseMotionListener(new MouseMotionListener(){
				public void mouseDragged(MouseEvent e){
					//System.out.printf("Drag\n");
			        if (mousePressed== true){
						int x,y;
						x = BigEyes.this.getLocationOnScreen().x + e.getX()-mirrorClickX;
						y = BigEyes.this.getLocationOnScreen().y + e.getY()-mirrorClickY;
						mainMirror.setLocation(x,y);
						setLocation(x,y);
			        }
				}
				public void mouseMoved(MouseEvent e){
					//System.out.printf("Move\n");
			        if (mousePressed== true){
						int x,y;
						x = BigEyes.this.getLocationOnScreen().x + e.getX()-mirrorClickX;
						y = BigEyes.this.getLocationOnScreen().y + e.getY()-mirrorClickY;
						mainMirror.setLocation(x,y);
						setLocation(x,y);
			        }
				}
			}
		);
		
		this.addKeyListener(new KeyListener(){
			public void keyReleased(KeyEvent e){
				if (e.getKeyCode()==112)
				{
					System.out.printf("press F1\n");
		            bigEyes.setVisible(false);
					mainMirror.setType(1);
		            bigEyes.setVisible(true);
				}
				if (e.getKeyCode()==113)
				{
					System.out.printf("press F2\n");
					mainMirror.setType(2);
				}
				if (e.getKeyCode()==114)
				{
					System.out.printf("press F3\n");
					mainMirror.setType(3);
				}
				if (e.getKeyCode()==115)
				{
					System.out.printf("press F4\n");
		            bigEyes.setVisible(false);
					mainMirror.setType(6);
		            bigEyes.setVisible(true);
				}
				if (e.getKeyCode()==116)
				{
					System.out.printf("press F5\n");
		            bigEyes.setVisible(false);
					mainMirror.setType(7);
		            bigEyes.setVisible(true);
				}
				if (e.getKeyCode()==117)
				{
					System.out.printf("press F6\n");
		            bigEyes.setVisible(false);
					mainMirror.setType(5);
		            bigEyes.setVisible(true);
				}
				if (e.getKeyCode()==118)
				{
					System.out.printf("press F7\n");
		            bigEyes.setVisible(false);
					mainMirror.setType(8);
		            bigEyes.setVisible(true);
				}
				if (e.getKeyCode()==120)
				{
					System.out.printf("press F9\n");
		            bigEyes.setVisible(false);
					mainMirror.setType(4);
		            bigEyes.setVisible(true);
				}
			}

			public void keyPressed(KeyEvent e) {
				// TODO Auto-generated method stub
				
			}

			public void keyTyped(KeyEvent e) {
				// TODO Auto-generated method stub
				
			}
		});
	}
	public void setBackground(int size)
	{
		//加背景++
		if (size==255)
			background = new ImageIcon(getClass().getResource("background.jpg"));  
		else
			background = new ImageIcon(getClass().getResource("backgroundLarge.jpg"));  
        JPanel panel = new JPanel()   
        {   
            /*
			 */
			private static final long serialVersionUID = 1L;

			protected void paintComponent(Graphics g)   
            {   
                g.drawImage(background.getImage(), 0, 0, null);   
                super.paintComponent(g);   
            }   
        };  
        panel.setOpaque( false );   
        panel.setPreferredSize( new Dimension(size, size) );   
        panel.setBounds(0,0,size,size);
        this.add(panel);
		//加背景--
	}
	public static void main(String arg[]){
		System.out.print("Program begin!\n");
		new BigEyes();
	}
}
