$(document).ready(function () {
    $('div.checkbox').click(function () {
        if ($(this).text().length > 0) {
            $(this).text('');
        } else {
            $(this).text('√');
        }
    });

    $('.level-1 img.img-1').click(function () {
        $(this).toggleClass('rotate90');
        $(this).parent().toggleClass('fold');
    });
});