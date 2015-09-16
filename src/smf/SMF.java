/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package smf;

import com.alee.laf.WebLookAndFeel;
import com.alee.extended.filechooser.WebDirectoryChooser;
import com.alee.utils.swing.DialogOptions;

import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 *
 * @author Imron02
 */
public class SMF extends JFrame {

    /**
     * @param args the command line arguments
     */
    
    static String path;
    
    public SMF() {
        initUI();
    }
    
    private void initUI() {
        initLookAndFeel();
        createMenuBar();
        createForm();
        
        setTitle("Show My Files");
        setSize(300, 160);
        ImageIcon frameIcon = new ImageIcon(this.getClass().getResource("/images/app.png"));
        setIconImage(frameIcon.getImage());
        setResizable(false);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    
    private static void initLookAndFeel() {
        WebLookAndFeel.install();
           
//        try {
//            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
//        }
//        catch (ClassNotFoundException e) {
//            System.err.println("Did you include the L&F library in the class path?");
//            System.err.println("Using the default look and feel.");
//        } 
//            
//        catch (UnsupportedLookAndFeelException e) {
//            System.err.println("Can't use the specified look and feel on this platform.");
//            System.err.println("Using the default look and feel.");
//        } 
//            
//        catch (Exception e) {
//            System.err.println("Couldn't get specified look and feel for some reason.");
//            System.err.println("Using the default look and feel.");
//            e.printStackTrace();
//        }
    }
    
    private void createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        ImageIcon exitIcon = new ImageIcon(this.getClass().getResource("/images/exit.png"));
        ImageIcon aboutIcon = new ImageIcon(this.getClass().getResource("/images/about.png"));
        
        JMenu fileMenu = new JMenu("File");
        fileMenu.setMnemonic(KeyEvent.VK_F);
        
        JMenu helpMenu = new JMenu("Help");
        helpMenu.setMnemonic(KeyEvent.VK_H);
        
        JMenuItem exitMenuItem = new JMenuItem("Exit", exitIcon);
        exitMenuItem.setMnemonic(KeyEvent.VK_E);
        exitMenuItem.setToolTipText("Exit Application");
        exitMenuItem.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
        
        JMenuItem helpMenuItem = new JMenuItem("About", aboutIcon);
        helpMenuItem.setMnemonic(KeyEvent.VK_A);
        helpMenuItem.setToolTipText("Abotu application");
        helpMenuItem.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(SMF.this, 
                            "This application is for unhide file and folder"
                            + " after malware virus attack",
                            "Error Message",
                            JOptionPane.INFORMATION_MESSAGE);
            }
        });
        
        fileMenu.add(exitMenuItem);
        helpMenu.add(helpMenuItem);
        menuBar.add(fileMenu);
        menuBar.add(helpMenu);
        
        setJMenuBar(menuBar);
    }
    
    private void createForm() {
        
        JLabel driveLabel = new JLabel("Drive Letter:");
        driveLabel.setBounds(10, 10, 80, 25);
        
        JTextField driveTextField = new JTextField();
        driveTextField.setBounds(85, 10, 160, 25);
        driveTextField.setEditable(false);
        
        JButton chooseButton = new JButton("...");
        chooseButton.setBounds(250, 10, 30, 25);
        
        JButton okButton = new JButton("Ok");
        okButton.setBounds(130, 70, 70, 30);
        
        JButton quitButton = new JButton("Quit");
        quitButton.setBounds(210, 70, 70, 30);
        
        JPanel panel = new JPanel();
        panel.setLayout(null);
        
        panel.add(driveLabel);
        panel.add(driveTextField);
        panel.add(chooseButton);
        panel.add(okButton);
        panel.add(quitButton);
        
        add(panel);
        
        chooseButton.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                WebDirectoryChooser chooser = new WebDirectoryChooser(SMF.this, 
                        "Select target directory");
                chooser.setVisible(true);
                if (chooser.getResult() == DialogOptions.OK_OPTION) {
                    final File file = chooser.getSelectedDirectory();
                    path = file.toString();
                    driveTextField.setText(path);
                }
//                JFileChooser chooser = new JFileChooser();
//                chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
//                chooser.setCurrentDirectory(chooser.getFileSystemView()
//                        .getParentDirectory(new File("C:\\")));
//                chooser.setDialogTitle("Select target directory");
                
//                int returnVal = chooser.showOpenDialog(SMF.this);
//                if (returnVal == JFileChooser.APPROVE_OPTION) {
//                    path = chooser.getSelectedFile().getAbsolutePath();
//                    driveTextField.setText(path);
//                }
            }
        });
        
        okButton.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                if(path == null || path.isEmpty()) {
                    JOptionPane.showMessageDialog(SMF.this, 
                            "Please choose drive/directory.",
                            "Error Message",
                            JOptionPane.ERROR_MESSAGE);
                } else {
                    System.out.println("Success");
                    fixDrive(path);
                }
            }
        });
        
        quitButton.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
    }
    
    private void fixDrive(String param) {
        String command = "attrib -s -h -a /s /d "+param+"\\*.*";
        Process p;
        try {
            p = Runtime.getRuntime().exec(command);
            p.waitFor();
            
            BufferedReader reader = new BufferedReader(
                    new InputStreamReader(p.getInputStream()));
            String line;
            while((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
                new SMF().setVisible(true);
            }
            
        });
    }
    
}
