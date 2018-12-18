/*class QueueItem {
  int outputX, outputY;
  Ray ray;
}

class Antialias {

  public:


  virtual std::queue<QueueItem> antialias(Ray &) = 0;
  virtual std::queue<QueueItem> outputUpdated (const View&) = 0;

}

class NoAntiAlias {
  std::queue<QueueItem> antialias(Ray &);
  std::queue<QueueItem> outputUpdated (const View&);
}

class EDAntiAlias {

  public:

  float threshold;

  EDAntiAlias (float th);

  std::queue<QueueItem> antialias(int outputX, int outputY);
  std::queue<QueueItem> outputUpdated (const View&);
}

*/
