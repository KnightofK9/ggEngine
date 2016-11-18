/**
 * Created by Knight of k9 on 12/11/2016.
 */
var Boot = function (game) {
    this.create = function () {
        game.state.start('editState');
    };
};