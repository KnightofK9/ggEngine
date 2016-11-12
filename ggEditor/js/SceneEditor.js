/**
 * Created by Knight of k9 on 12/11/2016.
 */
var SceneEditor = function(width,height,tileWidth, tileHeight, quadNodeWidth, quadNodeHeight){
    this.editState = null;
    this.bootState = null;
    var that = this;
    var init = function(){
        game = new Phaser.Game(width, height, Phaser.AUTO, 'gg-phaser');
        that.bootState = new Boot(game);
        that.editState = new EditState(game,tileWidth, tileHeight, quadNodeWidth,quadNodeHeight);
        game.state.add('boot',that.bootState);
        game.state.add('editState',that.editState);
        game.state.start('boot');
    };


    init();
};