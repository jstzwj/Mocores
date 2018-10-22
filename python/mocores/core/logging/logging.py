import logging


def init_logging(filename=None):
    LOG_FORMAT = "%(asctime)s - %(levelname)s - %(message)s"
    if(filename!=None):
        logging.basicConfig(filename=filename, level=logging.DEBUG, format=LOG_FORMAT)
    else:
        logging.basicConfig(level=logging.DEBUG, format=LOG_FORMAT)


def debug(*args, **kws):
    logging.debug(*args, **kws)
def info(*args, **kws):
    logging.info(*args, **kws)
def warning(*args, **kws):
    logging.warning(*args, **kws)
def error(*args, **kws):
    logging.error(*args, **kws)
def critical(*args, **kws):
    logging.critical(*args, **kws)