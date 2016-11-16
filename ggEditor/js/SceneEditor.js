/**
 * Created by Knight of k9 on 12/11/2016.
 */
var SceneEditor = function(name, width,height,tileWidth, tileHeight, quadNodeWidth, quadNodeHeight,json){
    this.editState = null;
    this.bootState = null;
    var that = this;
    var init = function(){
        game = new Phaser.Game(width, height, Phaser.AUTO, 'gg-phaser');
        that.bootState = new Boot(game);
        that.editState = new EditState(name, game,tileWidth, tileHeight, quadNodeWidth,quadNodeHeight,json);
        //if(json){
        //    that.editState.importState(json);
        //}
        game.state.add('boot',that.bootState);
        game.state.add('editState',that.editState);
        game.state.start('boot');
    };


    init();
};

