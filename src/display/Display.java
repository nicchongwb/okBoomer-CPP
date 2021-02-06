package display;

import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;

// Display class to create window display/etc in Launcher
public class Display {
    // Declare local variables
    private JFrame frame; // JFrame for window display of application
    private Canvas canvas; // Canvas object let us draw graphics(sprite,rect,etc) on our window/JFrame in this case
    private InventoryDisplay inventory; // JPanel for Inventory
    private ScoreboardDisplay scoreboard; // JPanel for Scoreboard

    private String title;
    private int width, height;

    private int counter = 0;

    // Constructor
    public Display(String title, int width, int height){
        this.title = title;
        this.width = width;
        this.height = height;

        // create inventory panel
        inventory = new InventoryDisplay();
        inventory.setPreferredSize(new Dimension(640, 60));
        JLabel invText = new JLabel("Inventory");
        inventory.add(invText);

        // create scoreboard
        scoreboard = new ScoreboardDisplay();
        //scoreboard.setLayout(new BorderLayout()); //uncomment to use borderlayout
        scoreboard.setPreferredSize(new Dimension(640,60));
        JLabel scoreText = new JLabel("Scoreboard");
        scoreboard.add(scoreText);

        createDisplay(); // Create Display/ Initialise JFrame
    }

    // Other methods
    private void createDisplay(){
        frame = new JFrame(title);
        frame.setSize(width, height);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Ensure process is killed upon closing
        frame.setResizable(false); // Disable window resize
        frame.setLocationRelativeTo(null); // Window will start in middle
        frame.setVisible(true); // Window to appear on screen

        // Initialise canvas object
        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height)); // Set canvas size according to this.width,height
        canvas.setMaximumSize(new Dimension(width, height));
        canvas.setMinimumSize(new Dimension(width, height)); // Ensure that canvas always stay within the width and height

        // KeyManager Input
        canvas.setFocusable(false); // So that JFrame will focus on itself

        // Final Step to Add canvas,etc onto our JFrame
        frame.add(canvas);
        frame.pack(); // Resize frame so that we can see all of the canvas without issues/ cutoffs

    }

    // Method to add inventory and scoreboard to the canvas
    public void createInvScore(){
        frame.add(this.scoreboard, BorderLayout.NORTH);
        frame.add(this.inventory, BorderLayout.SOUTH);
        frame.pack();
    }



    // Jpanel for inventory display
    class InventoryDisplay extends JPanel{
        // Constructor
        public InventoryDisplay() {
            setFocusable(false);  // so that this can receive key-events
            requestFocus();
        }

        // Override paintComponent to do custom drawing.
        @Override
        public void paintComponent(Graphics g) {
            Graphics2D g2d = (Graphics2D)g;  // if using Java 2D
            super.paintComponent(g2d);       // paint background
            setBackground(Color.LIGHT_GRAY);      // may use an image for background
        }

    }

    // Jpanel for scoreboard display
    class ScoreboardDisplay extends JPanel{
        // Constructor
        private int p1Health, p2Health;

        public ScoreboardDisplay() {
            p1Health = 0;
            p2Health = 0;
        }

        // Override paintComponent to do custom drawing.
        @Override
        public void paintComponent(Graphics g) {
            Graphics2D g2d = (Graphics2D)g;  // if using Java 2D
            super.paintComponent(g2d);       // paint background
            setBackground(Color.ORANGE);      // may use an image for background

        }

        // Paint function to update scoreboard. This is called via repaint()
        @Override
        public void paint(Graphics g){
            g.clearRect(0, 0, 640, 60);

            Graphics2D g2d = (Graphics2D)g;  // if using Java 2D
            super.paintComponent(g2d);       // paint background
            setBackground(Color.ORANGE);      // may use an image for background

            // Player(s) information includes: playerID/name, health
            g.drawString("Player 1: " + String.valueOf(p1Health) + "/10", 32, 30);
            g.drawString("Points: 0", 32, 45);


            g.drawString("Player 2: " + String.valueOf(p2Health) + "/10", 512, 30);
            g.drawString("Points: 0", 512, 45);

            // To see if scoreboard is updating
            g.drawString(String.valueOf(counter), 300, 45);
            counter += 1;

        }

        // Getter and Setter
        public int getP1Health() {
            return p1Health;
        }

        public void setP1Health(int p1Health) {
            this.p1Health = p1Health;
        }

        public int getP2Health() {
            return p2Health;
        }

        public void setP2Health(int p2Health) {
            this.p2Health = p2Health;
        }

    }

    // Getters
    public Canvas getCanvas(){
        return canvas;
    }

    public JFrame getFrame(){
        return frame;
    }

    public ScoreboardDisplay getScoreboard() {
        return scoreboard;
    }

    public void updateScoreboard(int p1Health, int p2Health) {
        this.scoreboard.setP1Health(p1Health);
        this.scoreboard.setP2Health(p2Health);
        this.scoreboard.repaint(); // calls the paint() in scoreboard
    }
}
