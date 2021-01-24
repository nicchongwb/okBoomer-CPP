package entities.creatures;

import gfx.Assets;
import okBoomer.Game;

import java.awt.*;

/* Usage: GameState class -> private Player player;
GameState constructor -> player = new Player(x,y);
GameState tick() -> player.tick();
GameState render() -> player.render(g);

 */

public class Player extends Creature{
    private static int playerCount = 0;
    private static int pixToMove = 16; // Amount of pixels to move

    // Player characteristics/attributes
    private String name;
    private final int pid; // Player ID
    private Game game;

    public Player(Game game, int x, int y) {
        super(x, y);
        this.game = game; // Help us access KeyManager
        pid = playerCount;
        playerCount++;
    }

    public String getName(){
        return name;
    }

    private void setName(String name){
        this.name = name;
    }

    @Override
    public void tick() {
        if (pid == 0){ // If pid == 0 for player 1
            if (game.getKeyManager().p1Up)
                y -= pixToMove;
            if (game.getKeyManager().p1Down)
                y += pixToMove;
            if (game.getKeyManager().p1Left)
                x -= pixToMove;
            if (game.getKeyManager().p1Right)
                x += pixToMove;
        }
        else if (pid == 1){ // It pid == 1 for player 2
            if (game.getKeyManager().p2Up)
                y -= pixToMove;
            if (game.getKeyManager().p2Down)
                y += pixToMove;
            if (game.getKeyManager().p2Left)
                x -= pixToMove;
            if (game.getKeyManager().p2Right)
                x += pixToMove;
        }

    }

    @Override
    public void render(Graphics g) {
        // Insert g.draw method to draw out player
        g.drawImage(Assets.player, x, y, null);
    }

}