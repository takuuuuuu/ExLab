var express = require('express');
var router = express.Router();

/* GET api listing. */
router.get('/version', function(req, res, next) {
  res.send({ 'version': '1.0.0' });
});

router.get('/echo', function(req, res, next) {
  res.send({ 'name': req.query.name });
});


router.get('/sum', function(req, res, next) {
  // Parse the query parameters to integers
  var a = parseInt(req.query.a);
  var b = parseInt(req.query.b);

  if (isNaN(a) || isNaN(b)) {
    res.status(400).send({ 'error': 'Invalid input' });
  } else {

    var sum = a + b;

    res.send({ 'result': sum });
  }
});

module.exports = router;
