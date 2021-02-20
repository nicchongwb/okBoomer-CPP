package interfaces;

/* StateManager Interface to manage our States in the Game.java */


import display.Display;
import gfx.Assets;
import gfx.UIImageButton;
import gfx.UIManager;
import okBoomer.ClickListener;
import okBoomer.Game;
import okBoomer.Handler;
import states.EndState;
import states.GameState;
import states.MenuState;
import states.State;

import javax.swing.*;

public interface StateManager {
    /* Method to switch the State of game
    *  handler = game instance
    *  state = targetState to switch to: MenuState, GameState, EndState*/
    static void switchState(Handler handler, String state){
        if (state == "MenuState"){
            State.setCurrentState(handler.getGame().menuState);
        }
        if (state == "GameState"){
            State.setCurrentState(handler.getGame().gameState);
        }
        if (state == "EndState"){
            State.setCurrentState(handler.getGame().endState);
        }

    }

    // initMenuUI -> initialise UI elements and click for the Menu State
    static void initMenuUI(Handler handler, UIManager uiManager){
        // Add Start Button object to UIManager's ArrayList
        System.out.println("making start button...");
        uiManager.addObject(new UIImageButton(200,200,256,128,Assets.btn_start, new ClickListener(){

            // Override onClick() to perform specific actions upon clicking START button
            @Override
            public void onClick() {
                handler.getMouseManager().setUIManager(null);
                System.out.println("start button");
                JTextField P1Field = new JTextField(10);
                JTextField P2Field = new JTextField(10);
                JPanel myPanel = new JPanel();
                myPanel.add(new JLabel("Player 1:"));
                myPanel.add(P1Field);
                myPanel.add(Box.createHorizontalStrut(20)); // a spacer
                myPanel.add(new JLabel("Player 2:"));
                myPanel.add(P2Field);

                int result = JOptionPane.showConfirmDialog(null, myPanel,
                        "Please Enter your name", JOptionPane.OK_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION) {

                    System.out.println("Player 1: " + P1Field.getText());
                    System.out.println("Player 2: " + P2Field.getText());

                    String p1fieldName = P1Field.getText();
                    String p2fieldName = P2Field.getText();
                    // Make input names to max length of 8
                    if (p1fieldName.length() > 8){
                        p1fieldName = p1fieldName.substring(0,8);
                    }
                    if (p2fieldName.length() > 8){
                        p2fieldName = p2fieldName.substring(0,8);
                    }
                    Display.setP1Name(p1fieldName);
                    Display.setP2Name(p2fieldName);
                    Jukebox.stopMusic();
                    Jukebox.playMusic("/res/audio/Invincible2.wav");
                    switchState(handler, "GameState");

                }else if(result == JOptionPane.CANCEL_OPTION){
                    System.out.println("Cancel");
                    handler.getMouseManager().setUIManager(uiManager);

                }
            }
        }));
    }

    // initEndUI -> initialise UI elements and click for the End State
    static void initEndUI(Handler handler, UIManager uiManager){
        System.out.println("making replay and quit button...");
        uiManager.addObject(new UIImageButton(200,200,256,128,Assets.btn_replay, new ClickListener(){
            @Override
            public void onClick() {
                handler.getMouseManager().setUIManager(null);
                switchState(handler, "GameState");
                System.out.println("play again button");
            }
        }));

        uiManager.addObject(new UIImageButton(200,350,256,128, Assets.btn_quit, new ClickListener(){
            @Override
            public void onClick() {
                handler.getMouseManager().setUIManager(null);
                System.out.println("quit button");
                System.exit(0);
            }
        }));
    }

    // This method will control the State of the game based on user's mouse click and keyboard input
    static void initUIManager(Handler handler, UIManager uiManager){
        //clear all buttons from objects array list
        uiManager.objects.clear();

        // Check for Current State of game and issue necessary methods
        if (State.getState() instanceof EndState) {

            System.out.println("ENDSTATE");
            initEndUI(handler, uiManager);
        }
        else if (State.getState() instanceof MenuState) {

            System.out.println("MENUSTATE");
            initMenuUI(handler, uiManager);
        }
    }
    


}